from django.contrib.auth.models import User
from django.db.models.signals import post_save, pre_save
from django.dispatch import receiver

from ask.models import UserProfile, Tag, QuestionLike, AnswerLike


@receiver(post_save, sender=User, dispatch_uid='save_new_user_profile')
def save_profile(sender, instance, created, **kwargs):
    user = instance
    if created:
        profile = UserProfile(user=user)
        profile.save()


@receiver(pre_save, sender=Tag, dispatch_uid='presave_clean_tag')
def save_tag(sender, instance, created, **kwargs):
    tag = instance
    tag.title = tag.title.strip(' \t\n\r')


@receiver(post_save, sender=QuestionLike, dispatch_uid='save_rating_update')
def save_tag(sender, instance, created, **kwargs):
    like = instance
    if like.is_like:
        like.question.rating += 1
    else:
        like.question.rating -= 1


@receiver(post_save, sender=AnswerLike, dispatch_uid='save_rating_answer_update')
def save_tag(sender, instance, created, **kwargs):
    like = instance
    if like.is_like:
        like.answer.rating += 1
    else:
        like.answer.rating -= 1
