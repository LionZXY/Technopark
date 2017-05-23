from django.conf.urls import url, include
from django.contrib import admin
from ask import views

urlpatterns = [
    url(r'^(?:(?P<pk>\d+)/)?$', views.index, name='index'),
    url(r'^hot', views.hot, name='hot'),
    url(r'^tag/(?P<tag_id>([a-zA-Zа-яА-Я ])+)?$', views.tag, name='tag'),
    url(r'^question/(?P<id>\d+)?$', views.question, name='question'),
    url(r'^user/settings', views.settings, name='settings'),
    url(r'^ask', views.ask, name='ask'),

    url(r'^login', views.login, name='login'),
    url(r'^signup', views.signup, name='signup'),
    url(r'^logout', views.logout, name='logout'),

    url(r'^api/v1/login', views.api_login, name='api_login'),
    url(r'^api/v1/logout', views.api_logout, name='api_logout'),
    url(r'^api/v1/signup', views.api_registration, name='api_signup'),
    url(r'^api/v1/ask', views.api_ask, name='api_ask'),
    url(r'^api/v1/answer', views.api_answer, name='api_answer'),
    url(r'^api/v1/like', views.api_like, name='api_like'),


]
