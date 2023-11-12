import requests 
from bs4 import BeautifulSoup 
  
class Jokes:
    def __init__(this): 
        # Making a GET request 
        r = requests.get('https://www.hellaentertainment.com/blog/celebrities/80-chuck-norris-jokes-for-his-80th-birthday/') 

        # Parsing the HTML 
        soup = BeautifulSoup(r.content, 'html.parser') 

        s = soup.find('div', class_= "entry-content template-color-red")
        this.lines = s.find_all('li') 

    def fetch_joke(this, joke_number) -> str:
        return this.lines[int(joke_number)].get_text()


  
