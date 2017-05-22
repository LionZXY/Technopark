import re

from django.contrib import auth
from django.contrib.auth.models import User
from django.contrib.sessions.models import Session
from django.core import validators
from django.core.exceptions import ValidationError
from django.core.paginator import Paginator, PageNotAnInteger, EmptyPage
from django.db import IntegrityError
from django.http import HttpResponse, Http404, HttpResponseBadRequest, HttpResponseRedirect, JsonResponse
from django.shortcuts import render
from django.utils.html import escape
from django.utils.http import is_safe_url
from django.views.decorators.csrf import csrf_exempt
from pygments.util import xrange

from ask.forms import LoginForm, UserRegistrationForm
from ask.models import Question, UserProfile


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


def tag(request):
    return render(request, "tag.html")


def login(request):
    return render(request, "login.html")


def signup(request):
    return render(request, "signup.html", {"form": UserRegistrationForm()})


def ask(request):
    return render(request, "ask.html")


def settings(request):
    return render(request, "settings.html")


def question(request, id=1):
    qst = None
    try:
        id = int(id)
    except ValueError:
        return HttpResponseBadRequest("Id must be int")
    if 0 < id <= Question.objects.count():
        qst = Question.objects.get(id)
    else:
        raise Http404("Question not found")
    return render(request, "question.html", {'question': qst})


def login(request):
    url = request.POST.get('continue')
    if request.user.is_authenticated():
        if is_safe_url(url):
            return HttpResponseRedirect(url)
        return render(request, "login.html", {'form': None})
    return render(request, "login.html", {'form': LoginForm()})


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
    user = request.user
    if user is not None:
        auth.logout(request)
        return JsonResponse({'status': 'ok'})
    else:
        return JsonResponse({'status': 'error',
                             'message': 'Вы не авторизованны'})


def api_registration(request):
    login = request.POST.get("username")
    email = request.POST.get("email")
    password1 = request.POST.get("password")
    password2 = request.POST.get("password2")

    error_fields = []
    if not login or len(login) == 0:
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

    if not re.compile("^([A-Za-z0-9]+)+$").match(login):
        return JsonResponse({'status': 'error',
                             'message': 'Неверный формат логина',
                             'fields': ['username']})

    try:
        user = User.objects.create(username=login,
                                   email=email,
                                   password=password1)
        user.save()
        user = UserProfile.objects.create(user=user)
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
