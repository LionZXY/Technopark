import re

from django.contrib import auth
from django.contrib.auth.models import User
from django.contrib.sessions.models import Session
from django.core import validators, serializers
from django.core.exceptions import ValidationError
from django.core.paginator import Paginator, PageNotAnInteger, EmptyPage
from django.db import IntegrityError
from django.forms import model_to_dict
from django.http import HttpResponse, Http404, HttpResponseBadRequest, HttpResponseRedirect, JsonResponse
from django.shortcuts import render
from django.utils.html import escape
from django.utils.http import is_safe_url
from django.views.decorators.csrf import csrf_exempt
from pygments.util import xrange

from ask.forms import LoginForm, UserRegistrationForm, AskForm, AnswerForm
from ask.models import Question, UserProfile, Tag, QuestionLike, Answer, AnswerLike


@csrf_exempt
def index(request, **kwargs):
    pk = kwargs.get('pk', 1) or 1
    data, paginator = select_page(Question.objects.new().all(), pk)
    return render(request, "index.html", {'questions': data, 'paginator': paginator})


def select_page(list_item, page):
    paginator = Paginator(list_item, 10)
    try:
        return paginator.page(page), paginator
    except PageNotAnInteger:
        raise Http404("Page not an integer")
    except EmptyPage:
        return paginator.page(paginator.num_pages), paginator


def hot(request):
    return render(request, "hot.html")


def tag(request, **kwargs):
    tag_id = kwargs.get('tag_id', None) or 1
    if tag_id is None:
        raise Http404("Тег не может быть пустым")

    try:
        tag = Tag.objects.get(title=tag_id)
    except Tag.DoesNotExist:
        raise Http404("Такого тега не существует")

    return render(request, "tag.html", {"tag": tag, "questions": tag.questions.all()})


def login(request):
    return render(request, "auth/login.html")


def signup(request):
    return render(request, "auth/signup.html", {"form": UserRegistrationForm()})


def ask(request):
    return render(request, "ask.html", {"form": AskForm()})


def settings(request):
    return render(request, "settings.html")


def question(request, id=1):
    qst = None
    try:
        id = int(id)
    except ValueError:
        return HttpResponseBadRequest("Id must be int")
    if 0 < id <= Question.objects.count():
        qst = Question.objects.get(id=id)
    else:
        raise Http404("Question not found")

    return render(request, "question.html", {'question': qst,
                                             'tags': qst.tags.all(),
                                             'answers': qst.answers.all(),
                                             'form': AnswerForm()})


def login(request):
    url = request.POST.get('continue')
    if request.user.is_authenticated():
        if is_safe_url(url):
            return HttpResponseRedirect(url)
        return render(request, "auth/login.html", {'form': None})
    return render(request, "auth/login.html", {'form': LoginForm()})


def logout(request):
    valid = True
    if request.user.is_authenticated():
        auth.logout(request)
        valid = True
    else:
        valid = False
    return render(request, "auth/logout.html", {"valid": valid})


def api_login(request):
    lgn = request.POST.get('login')
    password = request.POST.get('password')

    user = auth.authenticate(username=lgn, password=password)
    if user is not None:
        auth.login(request, user)
    else:
        return JsonResponse({'status': 'error', 'message': 'Не найден такой логин или пароль'})

    if user is not None:
        if user.is_active:
            return JsonResponse({'status': 'ok'})
        else:
            return JsonResponse({'status': 'error', 'message': 'Пользователь не активен'})


def api_logout(request):
    if request.user.is_authenticated():
        auth.logout(request)
        return JsonResponse({'status': 'ok'})
    else:
        return JsonResponse({'status': 'error',
                             'message': 'Вы не авторизованны'})


def api_registration(request):
    first_name = request.POST.get("first_name")
    last_name = request.POST.get("last_name")
    login_user = request.POST.get("username")
    email = request.POST.get("email")
    password1 = request.POST.get("password")
    password2 = request.POST.get("password2")

    error_fields = []
    if not first_name or len(first_name) == 0:
        error_fields.append("first_name")
    if not last_name or len(last_name) == 0:
        error_fields.append("last_name")
    if not login_user or len(login_user) == 0:
        error_fields.append("username")
    if not email or len(email) == 0:
        error_fields.append("email")
    if not password1 or len(password1) == 0:
        error_fields.append("password")
    if not password2 or len(password2) == 0:
        error_fields.append("password2")
    if len(error_fields) > 0:
        return JsonResponse({'status': 'error',
                             'message': 'Отсутсвует обязательный параметр',
                             'fields': error_fields})

    if password1 != password2:
        return JsonResponse({'status': 'error',
                             'message': 'Отсутсвует обязательный параметр',
                             'fields': ['password', 'password2']})
    try:
        validators.validate_email(email)
    except ValidationError:
        return JsonResponse({'status': 'error',
                             'message': 'Неверный формат почты',
                             'fields': ['email']})

    if not re.compile("^([A-Za-z0-9]+)+$").match(login_user):
        return JsonResponse({'status': 'error',
                             'message': 'Неверный формат логина',
                             'fields': ['username']})

    try:
        user = User.objects.create(username=login_user,
                                   email=email,
                                   password=password1)
        user.first_name = first_name
        user.last_name = last_name
        user.save()
    except IntegrityError:
        return JsonResponse({'status': 'error',
                             'message': 'Нарушена уникальность вводимых данных. Возможно, ваш пароль или логин уже '
                                        'зарегестрирован',
                             'fields': []})
    except:
        return JsonResponse({'status': 'error',
                             'message': 'Неизвестная ошибка сервера'})
    if user is not None:
        return JsonResponse({'status': 'ok'})

    else:
        return JsonResponse({'status': 'error',
                             'message': 'Что-то случилось непонятное :( Обратитесь к администратору'})


def api_ask(request):
    if not request.user.is_authenticated():
        return JsonResponse({'status': 'error',
                             'message': 'Ошибка доступа'})

    title = request.POST.get("title")
    text = request.POST.get("text")
    tags = request.POST.get("tags")  # TODO

    error_fields = []
    if not title or len(title) == 0:
        error_fields.append("title")
    if not text or len(text) == 0:
        error_fields.append("text")
    if not tags or len(tags) == 0:
        error_fields.append("tags")
    if len(error_fields) > 0:
        return JsonResponse({'status': 'error',
                             'message': 'Отсутсвует обязательный параметр',
                             'fields': error_fields})

    tags = tags.split(",")

    if len(tags) < 1:
        return JsonResponse({'status': 'error',
                             'message': 'Укажите как минимум один тег',
                             'fields': 'tags'})

    try:
        qst = Question.objects.create(title=title,
                                      full_question=text,
                                      author=request.user.userprofile)

        for tag in tags:
            Tag.objects.add_qst(tag, qst)

        qst.save()
    except IntegrityError:
        return JsonResponse({'status': 'error',
                             'message': 'Нарушена уникальность вводимых данных. Возможно, такой вопрос уже существует',
                             'fields': []})
    except:
        return JsonResponse({'status': 'error',
                             'message': 'Неизвестная ошибка сервера'})
    if qst is not None:
        return JsonResponse({'status': 'ok',
                             'answer': {
                                 'title': qst.title,
                                 'id': qst.id,
                                 'question': qst.full_question
                             }})

    else:
        return JsonResponse({'status': 'error',
                             'message': 'Что-то случилось непонятное :( Обратитесь к администратору'})


def api_like(request):
    is_questions = request.POST.get("question", True)
    id = request.POST.get("id", None)
    is_like = request.POST.get("is_like", True)
    rating = 0

    if not request.user.is_authenticated():
        return JsonResponse({'status': 'error',
                             'message': 'Эта операция доступна только авторизованным пользователям'})

    if not id:
        return JsonResponse({'status': 'error',
                             'message': 'Отсутсвует id'})

    if is_questions:
        try:
            question = Question.objects.get(id=id)
        except Question.DoesNotExist:
            return JsonResponse({'status': 'error',
                                 'message': 'Такого вопроса не существует'})
        like, created = QuestionLike.objects.get_or_create(question=question, by_user=request.user)
        rating = question.rating
    else:
        try:
            answer = Answer.objects.get(id=id)
        except Question.DoesNotExist:
            return JsonResponse({'status': 'error',
                                 'message': 'Такого ответа не существует'})
        like, created = AnswerLike.objects.get_or_create(answer=answer, by_user=request.user)
        rating = answer.rating
    like.is_like = is_like
    like.save()
    return JsonResponse({'status': 'ok',
                         'answer': {
                             'rating': rating
                         }})


def api_answer(request):
    text = request.POST.get('text')
    question_id = request.POST.get('question_id')

    if not request.user.is_authenticated():
        return JsonResponse({'status': 'error',
                             'message': 'Эта операция доступна только авторизованным пользователям'})

    if not text:
        return JsonResponse({'status': 'error',
                             'message': 'Поле text обязательно',
                             'fields': 'text'})

    try:
        question = Question.objects.get(id=question_id)
    except Question.DoesNotExist:
        return JsonResponse({'status': 'error',
                             'message': 'Такого вопроса не существует'})
    Answer.objects.create(answer_text=text, question=question, by_user=request.user.userprofile)

    return JsonResponse({'status': 'ok'})
