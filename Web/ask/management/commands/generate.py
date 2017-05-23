import string
import random
from django.core.management.base import BaseCommand, CommandError
from django.contrib.auth.models import User

from ask.models import Question


class Command(BaseCommand):
    help = 'Adds a question with a random title and text'

    def handle(self, *args, **options):
        for i in range(1000):
            question = Question(title=self.text_gen(), full_question=self.text_gen(40) + "?",
                                author=User.objects.get(id=1).userprofile)
            question.save()
            self.stdout.write(self.style.SUCCESS('Successfully created question ' + question.title
                                                 + ' with text ' + question.full_question))

    @staticmethod
    def text_gen(size=6, chars=string.ascii_lowercase):
        return ''.join(random.choice(chars) for _ in range(size))
