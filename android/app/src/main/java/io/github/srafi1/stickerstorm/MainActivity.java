package io.github.srafi1.stickerstorm;

import android.content.Intent;
import android.graphics.Bitmap;
import android.provider.ContactsContract;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.nex3z.flowlayout.FlowLayout;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    static final int REQUEST_IMAGE_CAPTURE_FOR_REF_OBJECT = 1;
    static final int REQUEST_IMAGE_CAPTURE_FOR_LAPTOP = 2;
    static final int REQUEST_IMAGE_CAPTURE_FOR_STICKER = 3;
    Bitmap refImage;
    ImageView refImageView;
    Bitmap laptopImage;
    ImageView laptopImageView;
    ArrayList<Bitmap> stickerImages;
    FlowLayout stickerImageLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        refImageView = findViewById(R.id.refImage);
        laptopImageView = findViewById(R.id.laptopImage);
        stickerImageLayout = findViewById(R.id.stickerImageLayout);
        stickerImages = new ArrayList<Bitmap>();
    }

    public void takeRefImage(View view) {
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
            startActivityForResult(takePictureIntent, REQUEST_IMAGE_CAPTURE_FOR_REF_OBJECT);
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (resultCode == RESULT_OK) {
            Bundle extras = data.getExtras();
            Bitmap imageBitmap = (Bitmap) extras.get("data");
            switch (requestCode) {
                case REQUEST_IMAGE_CAPTURE_FOR_REF_OBJECT:
                    refImage = imageBitmap;
                    refImageView.setImageBitmap(imageBitmap);
                    break;
                case REQUEST_IMAGE_CAPTURE_FOR_LAPTOP:
                    laptopImage = imageBitmap;
                    laptopImageView.setImageBitmap(imageBitmap);
                    break;
                case REQUEST_IMAGE_CAPTURE_FOR_STICKER:
                    stickerImages.add(imageBitmap);
                    ImageView newImageView = new ImageView(this);
                    newImageView.setPadding(5, 5, 5, 5);
                    newImageView.setImageBitmap(imageBitmap);
                    stickerImageLayout.addView(newImageView, 0);
                    break;
            }
        }
    }

    public void takeLaptopImage(View view) {
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
            startActivityForResult(takePictureIntent, REQUEST_IMAGE_CAPTURE_FOR_LAPTOP);
        }
    }

    public void takeStickerImage(View view) {
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
            startActivityForResult(takePictureIntent, REQUEST_IMAGE_CAPTURE_FOR_STICKER);
        }
    }

    public void sendImages(View view) {
        if (refImage != null && laptopImage != null && stickerImages.size() != 0) {
            Toast.makeText(this, "Sending images", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Incomplete form", Toast.LENGTH_SHORT).show();
        }
    }
}
