from django.core.cache import caches, cache
from django.core.management.base import BaseCommand, CommandError


class Command(BaseCommand):
    help = 'Update cache global variables'

    def handle(self, *args, **options):
        cache.set('top_tags', {})
        cache.set('test', 'test')
        self.stdout.write("Cache is completed!")
