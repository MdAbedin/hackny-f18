from bottle import route, run, template, static_file, get, post, request, BaseRequest, Bottle, abort
import secret
import requests

@route('/search')
def send_static():
	res = google_req('facebook')['items'][0]
	print(res)
	obj = { 'title': res['pagemap']['metatags'][0]['og:site_name'],
			'description': res['snippet'],
			'url': res['formattedUrl'],
			'img': res['pagemap']['cse_thumbnail'][0]['src'] }
	return obj

def google_req(query):
    url = 'https://www.googleapis.com/customsearch/v1' 
    params = {'q': query, 'key': secret.api_key, 'cx': '003997601241135407106:qwbffm000to'}
    r = requests.get(url, params=params)
    return r.json()

run(host="0.0.0.0", port=5000)