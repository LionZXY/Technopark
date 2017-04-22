from django.conf.urls import url, include
from django.contrib import admin
from ask import views

urlpatterns = [
    url(r'^(?:(?P<pk>\d+)/)?$', views.index, name='index'),
    url(r'^hot', views.hot, name='hot'),
    url(r'^tag/[a-zA-Z]', views.tag, name='tag'),
    url(r'^question/(?P<id>\d+)?$', views.question, name='question'),
    url(r'^login', views.login, name='login'),
    url(r'^signup', views.signup, name='signup'),
    url(r'ask', views.ask, name='ask')
]