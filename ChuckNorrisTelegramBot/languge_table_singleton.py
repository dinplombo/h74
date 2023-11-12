import json

class Singleton:
    __instance = None
    @staticmethod 
    def get_instance():
        if Singleton.__instance == None:
            Singleton()
        return Singleton.__instance

    def __init__(self):
        
        if Singleton.__instance != None:
            raise Exception("This class is a singleton!")
        else:
            Singleton.__instance = self
            f = open('language.json')
            print('again')
            self.languge_table = json.load(f)

    def get_table(self):
        return self.languge_table

            