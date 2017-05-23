# -*- coding: utf-8 -*-
import datetime

from django.contrib.auth.models import User, AbstractUser
from django.contrib.sessions.models import Session
from django.db import models
from django.utils.timezone import utc

from ask.managers import QuestionManager, LikeManager, UserManager, TagManager


class UserProfile(models.Model):
    avatar = models.ImageField(null=True, blank=True, verbose_name=u"аватар")
    register_date = models.DateField(null=False, blank=True, auto_now_add=True, verbose_name=u"дата регистрации")
    rating = models.IntegerField(blank=True, default=0, verbose_name=u"рейтинг")
    user = models.OneToOneField(User, related_name='userprofile', null=False, verbose_name="user")
    objects = UserManager()

    # TODO

    def __unicode__(self):
        return self.user.username

    class Meta:
        verbose_name = u'пользователь'
        verbose_name_plural = u'пользователи'


class Tag(models.Model):
    title = models.CharField(max_length=50, null=False, verbose_name=u"название тега")
    objects = TagManager()

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
    tags = models.ManyToManyField(Tag, related_name='questions', verbose_name="тег")
    objects = QuestionManager()

    def is_actuals(self):
        now = datetime.datetime.utcnow().replace(tzinfo=utc)
        month_dif = (now - self.date).month
        return month_dif > 2

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name = u'вопрос'
        verbose_name_plural = u'вопросы'


class Answer(models.Model):
    answer_text = models.CharField(max_length=8192, null=False, verbose_name="ответ")
    rating = models.IntegerField(default=0, blank=True, verbose_name=u"рейтинг")
    by_user = models.ForeignKey(UserProfile, null=False, verbose_name="пользователь")
    question = models.ForeignKey(Question, related_name='answers', null=False, verbose_name="вопрос")

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

# Create your models here.
