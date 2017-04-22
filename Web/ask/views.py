from django.core.paginator import Paginator, PageNotAnInteger, EmptyPage
from django.http import HttpResponse, Http404, HttpResponseBadRequest
from django.shortcuts import render
from django.utils.html import escape
from django.views.decorators.csrf import csrf_exempt
from pygments.util import xrange

questions = []
for i in range(1, 30):
    questions.append({
        'title': 'title ' + str(i),
        'id': i,
        'text': 'text' + str(i),
    })


@csrf_exempt
def index(request, **kwargs):
    pk = kwargs.get('pk', 1) or 1
    data, paginator = select_page(questions, pk)
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
    return render(request, "signup.html")


def ask(request):
    return render(request, "ask.html")


def question(request, id=1):
    question = None
    try:
        id = int(id)
    except ValueError:
        return HttpResponseBadRequest("Id must be int")
    if 0 < id <= len(questions):
        question = questions[id]
    else:
        raise Http404("Question not found")
    return render(request, "question.html", {'question': question})

