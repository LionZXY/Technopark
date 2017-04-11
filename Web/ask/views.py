from django.http import HttpResponse
from django.shortcuts import render
from django.utils.html import escape
from django.views.decorators.csrf import csrf_exempt


@csrf_exempt
def index(request):
    data = []
    if request.method == 'GET':
        data = request.GET
    elif request.method == 'POST':
        data = request.POST
    return render(request, "hello.html", {'method': request.method, 'data': data})


def test_static(request):
    return render(request, "static.html")
