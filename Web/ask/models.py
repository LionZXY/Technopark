# -*- coding: utf-8 -*-
from django.contrib.auth.models import User
from django.db import models

from ask.managers import QuestionManager, TagManager, LikeManager


class UserProfile(models.Model):
    avatar = models.ImageField(null=True, blank=True, verbose_name=u"аватар")
    register_date = models.DateField(null=False, blank=True, auto_now_add=True, verbose_name=u"дата регистрации")
    user = models.OneToOneField(User, null=False, blank=False, verbose_name=u"пользователь")
    rating = models.IntegerField(blank=True, default=0, verbose_name=u"рейтинг")
    #TODO

    def __unicode__(self):
        return self.user.username

    class Meta:
        verbose_name = u'пользователь'
        verbose_name_plural = u'пользователи'


class Question(models.Model):
    title = models.CharField(max_length=255, null=False, verbose_name="вопрос")
    full_question = models.CharField(max_length=8192, null=False, verbose_name="полный вопрос")
    author = models.ForeignKey(UserProfile, null=False, verbose_name="пользователь")
    date = models.DateField(null=False, blank=True, auto_now_add=True, verbose_name=u"дата создания вопроса")
    rating = models.IntegerField(default=0, blank=True, verbose_name=u"рейтинг")
    objects = QuestionManager()

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name = u'вопрос'
        verbose_name_plural = u'вопросы'


class Answer(models.Model):
    answer_text = models.CharField(max_length=8192, null=False, verbose_name="ответ")
    by_user = models.ForeignKey(UserProfile, null=False, verbose_name="пользователь")
    question = models.ForeignKey(Question, null=False, verbose_name="вопрос")

    def __unicode__(self):
        return self.answer_text

    class Meta:
        verbose_name = u'ответ'
        verbose_name_plural = u'ответы'


class Tag(models.Model):
    title = models.ImageField(null=False, verbose_name=u"название тега")

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name = u'тег'
        verbose_name_plural = u'теги'


class Like(models.Model):
    by_user = models.ForeignKey(User, null=False, verbose_name=u"пользователь")
    is_like = models.BooleanField(blank=True, default=True, verbose_name=u"лайк")

    def __unicode__(self):
        return "Лайк пользователя " + self.by_user.username

    class Meta:
        verbose_name = u'лайк'
        verbose_name_plural = u'лайки'


class TagTable(models.Model):
    question = models.ForeignKey(Question, null=False, verbose_name=u"вопрос")
    tag = models.ForeignKey(Tag, null=False, verbose_name=u"тег")
    objects = TagManager()

    def __unicode__(self):
        return str(self.tag) + str(self.question)

    class Meta:
        verbose_name = u"таблица тегов"
        verbose_name_plural = u"таблицы тегов"


class LikeTable(models.Model):
    like = models.ForeignKey(Like, null=False, verbose_name=u"лайк")
    question = models.ForeignKey(Question, null=False, verbose_name=u"вопрос")
    objects = LikeManager()

    def __unicode__(self):
        return str(self.like) + str(self.question)

    class Meta:
        verbose_name = u"таблица лайков"
        verbose_name_plural = u"таблицы лайков"

# Create your models here.
