# -*- coding: utf-8 -*-
# Generated by Django 1.10.3 on 2017-04-22 11:37
from __future__ import unicode_literals

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('ask', '0002_answer'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='answer',
            options={'verbose_name': 'ответ', 'verbose_name_plural': 'ответы'},
        ),
    ]
