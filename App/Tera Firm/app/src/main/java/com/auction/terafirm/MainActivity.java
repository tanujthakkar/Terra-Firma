package com.auction.terafirm;

import android.support.annotation.NonNull;
import android.support.v4.app.NotificationBuilderWithBuilderAccessor;
import android.support.v4.app.NotificationCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Window;
import android.widget.ImageView;
import android.widget.TextView;

import com.google.firebase.FirebaseApp;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.InternalHelpers;
import com.google.firebase.database.ValueEventListener;

import java.net.Inet4Address;

public class MainActivity extends AppCompatActivity {

    // TextView Variables
    TextView tv_temp;
    TextView tv_humidity;
    TextView tv_light;
    ImageView status;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        FirebaseApp.initializeApp(this);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getSupportActionBar().hide();
        setContentView(R.layout.activity_main);

        FirebaseDatabase database = FirebaseDatabase.getInstance();
        DatabaseReference myRef = database.getReference();

        // Temperature Firebase Variable
        final DatabaseReference temperature = myRef.child("/temperature");

        // Humidity Firebase Variable
        final DatabaseReference humidity = myRef.child("/humidity");

        // Light Intensity Firebase Variable
        final DatabaseReference light = myRef.child("/light");

        tv_temp = (TextView)findViewById(R.id.tv_temp);
        tv_humidity = (TextView)findViewById(R.id.tv_humidity);
        tv_light = (TextView)findViewById(R.id.tv_light);
        status = (ImageView)findViewById(R.id.status);

        temperature.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                int value = dataSnapshot.getValue(int.class);
                tv_temp.setText("Temperature :" + Integer.toString(value));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        humidity.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                int value = dataSnapshot.getValue(int.class);
                tv_humidity.setText("Humidity : " + Integer.toString(value));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        light.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                int value = dataSnapshot.getValue(int.class);
                if(value >= 70) {
                    status.setImageResource(R.drawable.status_inactive);
                } else {
                    status.setImageResource(R.drawable.status_active);
                }
                tv_light.setText(Integer.toString(value));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });
    }
}
