# -*- coding: utf-8 -*-
# Generated by Django 1.10.3 on 2017-05-23 05:40
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('ask', '0007_auto_20170523_0451'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='tagtable',
            name='question',
        ),
        migrations.RemoveField(
            model_name='tagtable',
            name='tag',
        ),
        migrations.AlterField(
            model_name='question',
            name='tags',
            field=models.ManyToManyField(related_name='questions', to='ask.Tag', verbose_name='тег'),
        ),
        migrations.DeleteModel(
            name='TagTable',
        ),
    ]