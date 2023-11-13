import os
import telebot
import os
import json
import time

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
    if(message.text.isdigit() == False):
        sign_handler(message)
    if(0 > int(message.text) or int(message.text) > 100):
        sent_msg = bot.send_message(message.chat.id, 'joke number is between 1 - 100')
        bot.register_next_step_handler(sent_msg, joke_handler, languge)
    else:
        js = Jokes()
        text = js.fetch_joke(message.text)
        tr = Translator()
        sent_msg = bot.send_message(message.chat.id, tr.translate(languge, text))
        bot.register_next_step_handler(sent_msg, joke_handler, languge)
    
while True:
    try:
        bot.infinity_polling()
    except Exception:
        time.sleep(15)