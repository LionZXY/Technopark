from django.db import models


class QuestionManager(models.Manager):
    def hot(self):
        return self.order_by('-rating')[:50]

    def new(self):
        return self.order_by('-date')


class TagManager(models.Manager):
    def by_tag(self, tag):
        return self.filter(tag__title=tag).values_list('question').all()


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
