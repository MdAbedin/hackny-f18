from flask import Flask, flash, render_template, request, session, redirect, url_for
from flask_uploads import UploadSet, configure_uploads, IMAGES
import util.vision as vs

app = Flask(__name__)

photos = UploadSet('photos', IMAGES)
app.config['UPLOADED_PHOTOS_DEST'] = 'static/img'
configure_uploads(app, photos)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/stickers')
def stickers():
    num_stickers = 7
    return render_template('stickers.html', stickers=[i for i in range(num_stickers)], numStickers=num_stickers)

@app.route('/arranging')
def arranging():
    num_stickers = 7
    return render_template('arranging.html', stickers=[i for i in range(num_stickers)], numStickers=num_stickers)

@app.route('/arranged')
def arranged():
    return render_template('arranged.html')

@app.route('/explore')
def explore():
    return render_template('explore.html')

@app.route('/upload', methods=['POST'])
def upload():
    if request.method == 'POST' and 'photo' in request.files:
        img_name = photos.save(request.files['photo'])
        print "img name: ", img_name

    return render_template('explore.html', companies=vs.get_companies(img_name))

if __name__ == "__main__":
    app.debug = True
    app.run()
