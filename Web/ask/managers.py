from django.db import models
from django.db.models import Count
from django.template.loaders import cached
from django.core.cache import caches, cache


class QuestionManager(models.Manager):
    def hot(self):
        return self.order_by('-rating')[:50]

    def new(self):
        return self.order_by('-date')


class TagManager(models.Manager):
    def add_qst(self, tag_str, question):
        tag, created = self.get_or_create(title=tag_str)
        question.tags.add(tag)
        return tag

    def by_tag(self, tag_str):
        return self.filter(title=tag_str).first().questions.all()

    def popular(self):
        return cache.get('test')


class LikeManager(models.Manager):
    def by_question(self, question_id):
        return self.filter(question__id=question_id).values_list('like')

    def get_rating(self, question_id):
        rating = 0
        likes = self.filter(question__id=question_id).values_list('like').all()
        for like in likes:
            if like.is_like:
                rating += 1
            else:
                rating -= 1
        return rating

    def add_like(self, question, like):
        self.create(question=question, like=like)
        question.rating = self.get_rating(question.id)
        question.save()


class UserManager(models.Manager):
    def get_user(self, login):
        try:
            return self.get(login=login)
        except self.DoesNotExist:
            return None
