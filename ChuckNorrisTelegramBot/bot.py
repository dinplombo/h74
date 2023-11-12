import os
import telebot
import os
import json

from dotenv import load_dotenv
from translator import Translator
from jokes_data import Jokes
from languge_table_singleton import Singleton

load_dotenv()

TOKEN = os.getenv("TOKEN")

bot = telebot.TeleBot(TOKEN)

@bot.message_handler(func=lambda msg: True)
def sign_handler(message):
    s = Singleton.get_instance()   
    languges = s.get_table()
    lower_languge = message.text.lower()
    for languge in languges:
        if languge in lower_languge:
            sent_msg = bot.send_message(message.chat.id, 'no problem') 
            bot.register_next_step_handler(sent_msg, joke_handler, languges[languge])
            return
    
    bot.send_message(message.chat.id, 'this languge is nonexistent')


def joke_handler(message, languge):
    js = Jokes()
    text = js.fetch_joke(message.text)
    tr = Translator()

    bot.send_message(message.chat.id, tr.translate(languge, text))
    

bot.infinity_polling()