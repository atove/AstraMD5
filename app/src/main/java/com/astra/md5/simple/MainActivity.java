package com.astra.md5.simple;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.astra.md5jni.SignTool;


public class MainActivity extends AppCompatActivity {

    private EditText etSignText;
    private Button btnSign;
    private TextView tvSignResult;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        etSignText = (EditText) findViewById(R.id.et_sign_text);
        btnSign = (Button) findViewById(R.id.btn_sign);
        tvSignResult = (TextView) findViewById(R.id.tv_sign_result);

        Log.d("签名", "   ");
        btnSign.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String unSignText = etSignText.getText().toString();
                if (TextUtils.isEmpty(unSignText)){
                    Toast.makeText(MainActivity.this, "请输入要签名的文字", Toast.LENGTH_LONG);
                }else {
                    String signText = SignTool.sign(MainActivity.this, unSignText);
                    tvSignResult.setText(signText);
                }
            }});
    }
}
