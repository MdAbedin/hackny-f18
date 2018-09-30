import io
from google.cloud import vision
from google.cloud.vision import types

known_companies = [
    'major league hacking',
    'facebook',
    'instagram',
    'giphy',
    'github',
    'instagram',
    'messenger',
    'oculus',
    'whatsapp',
    'google',
    'google chrome',
    'chrome',
    'android',
    'kindsouls',
    'kind souls',
    'mlh',
    'stuyhacks',
    'stuy hacks',
    'replit',
    'repl.it',
    'cyberstuy',
    'cyber stuy',
    'pennapps',
    'penn apps',
    'hack nyu',
    'hacknyu',
    'qualcomm',
    'amazon',
    'amazonrobotics',
]

def get_path(img_name):
    return "./static/img/" + img_name

def get_companies(img_name):
    path = get_path(img_name)

    labels = get_labels(path)
    print labels

    companies = []

    for label in labels:
        for company in known_companies:
            if company.lower() in label.lower():
                companies.append(company)

    return companies

def get_labels(path):
    path
    labels = detect_web(path) + detect_text(path)

    return labels

def detect_web(path):
    client = vision.ImageAnnotatorClient()

    if path.startswith('http') or path.startswith('gs:'):
        image = types.Image()
        image.source.image_uri = path

    else:
        with io.open(path, 'rb') as image_file:
            content = image_file.read()

        image = types.Image(content=content)

    web_detection = client.web_detection(image=image).web_detection

    results = []

    if web_detection.web_entities:
        results = [result.description.strip() for result in web_detection.web_entities if result.description]

    return results

def detect_text(path):
    """Detects text in the file."""
    client = vision.ImageAnnotatorClient()

    with io.open(path, 'rb') as image_file:
        content = image_file.read()

    image = vision.types.Image(content=content)

    response = client.text_detection(image=image)
    texts = response.text_annotations

    results = [text.description.strip() for text in texts if text.description]

    return results

if __name__ == '__main__':
    path = get_path("mlh2.jpg")

    print path
    print detect_text(path)
