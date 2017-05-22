# -*- coding: utf-8 -*-
from django.contrib.auth.models import User, AbstractUser
from django.contrib.sessions.models import Session
from django.db import models

from ask.managers import QuestionManager, TagManager, LikeManager, UserManager


class UserProfile(models.Model):
    avatar = models.ImageField(null=True, blank=True, verbose_name=u"аватар")
    register_date = models.DateField(null=False, blank=True, auto_now_add=True, verbose_name=u"дата регистрации")
    rating = models.IntegerField(blank=True, default=0, verbose_name=u"рейтинг")
    user = models.OneToOneField(User, null=False, verbose_name="user")
    objects = UserManager()

    # TODO

    def __unicode__(self):
        return self.user.username

    class Meta:
        verbose_name = u'пользователь'
        verbose_name_plural = u'пользователи'


class Tag(models.Model):
    title = models.ImageField(null=False, verbose_name=u"название тега")

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name = u'тег'
        verbose_name_plural = u'теги'


class Question(models.Model):
    title = models.CharField(max_length=255, null=False, verbose_name="вопрос")
    full_question = models.CharField(max_length=8192, null=False, verbose_name="полный вопрос")
    author = models.ForeignKey(UserProfile, null=False, verbose_name="пользователь")
    date = models.DateField(null=False, blank=True, auto_now_add=True, verbose_name=u"дата создания вопроса")
    rating = models.IntegerField(default=0, blank=True, verbose_name=u"рейтинг")
    tags = models.ManyToManyField(Tag, verbose_name="тег")
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


class Like(models.Model):
    by_user = models.ForeignKey(User, null=False, verbose_name=u"пользователь")
    is_like = models.BooleanField(blank=True, default=True, verbose_name=u"лайк")
    objects = LikeManager()

    def __unicode__(self):
        return "Лайк пользователя " + self.by_user.username

    class Meta:
        abstract = True
        verbose_name = u'лайк'
        verbose_name_plural = u'лайки'


class QuestionLike(Like):
    question = models.ForeignKey(Question, null=False, verbose_name="вопрос")

    def __unicode__(self):
        return "Лайк пользователя " + self.by_user.username + " на вопрос " + self.question.title

    class Meta:
        unique_together = ("question", "by_user")


class AnswerLike(Like):
    answer = models.ForeignKey(Answer, null=False, verbose_name="ответ")

    def __unicode__(self):
        return "Лайк пользователя " + self.by_user.username + " на ответ " + self.answer.answer_text

    class Meta:
        unique_together = ("answer", "by_user")


class TagTable(models.Model):
    question = models.ForeignKey(Question, null=False, verbose_name=u"вопрос")
    tag = models.ForeignKey(Tag, null=False, verbose_name=u"тег")
    objects = TagManager()

    def __unicode__(self):
        return str(self.tag) + str(self.question)

    class Meta:
        verbose_name = u"таблица тегов"
        verbose_name_plural = u"таблицы тегов"

# Create your models here.
