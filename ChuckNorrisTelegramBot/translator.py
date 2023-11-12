import requests, uuid, json

class Translator:
  def __init__(this):
    key = "9507f25ee01244769e525843eba50363"
    location = "eastus"

    endpoint = "https://api.cognitive.microsofttranslator.com"
    path = '/translate'
    this.constructed_url = endpoint + path

    this.headers = {
        'Ocp-Apim-Subscription-Key': key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json',
        'X-ClientTraceId': str(uuid.uuid4())
    }

  def translate(this, languge, joke) -> str:
    params = {
        'api-version': '3.0',
        'from': 'en',
        'to': [languge]
    }

    body = [{
        'text': joke
    }]

    request = requests.post(this.constructed_url, params=params, headers=this.headers, json=body)
    response = request.json()

    
    translated_text = response[0]['translations'][0]['text']
    return translated_text

