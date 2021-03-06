# -*- coding: utf-8 -*-
# Generated by Django 1.10.3 on 2017-05-16 15:26
from __future__ import unicode_literals

from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
        ('ask', '0004_auto_20170422_1149'),
    ]

    operations = [
        migrations.CreateModel(
            name='AnswerLike',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('is_like', models.BooleanField(default=True, verbose_name='лайк')),
                ('answer', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='ask.Answer', verbose_name='ответ')),
                ('by_user', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to=settings.AUTH_USER_MODEL, verbose_name='пользователь')),
            ],
        ),
        migrations.CreateModel(
            name='QuestionLike',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('is_like', models.BooleanField(default=True, verbose_name='лайк')),
                ('by_user', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to=settings.AUTH_USER_MODEL, verbose_name='пользователь')),
            ],
        ),
        migrations.RemoveField(
            model_name='like',
            name='by_user',
        ),
        migrations.RemoveField(
            model_name='liketable',
            name='like',
        ),
        migrations.RemoveField(
            model_name='liketable',
            name='question',
        ),
        migrations.RenameField(
            model_name='question',
            old_name='by_user',
            new_name='author',
        ),
        migrations.AddField(
            model_name='question',
            name='tags',
            field=models.ManyToManyField(to='ask.Tag', verbose_name='тег'),
        ),
        migrations.DeleteModel(
            name='Like',
        ),
        migrations.DeleteModel(
            name='LikeTable',
        ),
        migrations.AddField(
            model_name='questionlike',
            name='question',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='ask.Question', verbose_name='вопрос'),
        ),
        migrations.AlterUniqueTogether(
            name='questionlike',
            unique_together=set([('question', 'by_user')]),
        ),
        migrations.AlterUniqueTogether(
            name='answerlike',
            unique_together=set([('answer', 'by_user')]),
        ),
    ]
