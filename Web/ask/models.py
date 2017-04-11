# -*- coding: utf-8 -*-

from django.db import models


class Article(models.Model):
    title = models.CharField(max_length=255, verbose_name=u"Заголовок")
    text = models.TextField(verbose_name=u"Текст")
    is_published = models.BooleanField(default=False, blank=True, verbose_name="Публик")
    author = models.ForeignKey('Author', verbose_name="Автор")

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name = u'Статья'
        verbose_name_plural = u'Статьи'


class Author(models.Model):
    name = models.CharField(max_length=255, verbose_name="Имя")

    def __unicode__(self):
        return self.name

    class Meta:
        verbose_name = u'Автор'
        verbose_name_plural = u'Авторы'

# Create your models here.
