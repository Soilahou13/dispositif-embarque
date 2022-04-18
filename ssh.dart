// @dart=2.9

import 'dart:async';
import 'package:flutter/services.dart';
import 'package:flutter/material.dart';
import 'package:ssh/ssh.dart';
import 'ssh2.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'SSH Raspi',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: Page2(),
    );
  }
}

class Page2 extends StatefulWidget {
  @override
  _Page2 createState() => _Page2();
}

class _Page2 extends State<Page2> {
  String _test = '';

  Future<void> connexion() async {
    final pi = new SSHClient(
      host: "10.3.141.1",
      port: 22,
      username: "pi",
      passwordOrKey: "raspberry",
    );
    String result;
    String test;
    try {
      result = await pi.connect();
      if (result == "session_connected")
        test = await pi.execute("python trotinette.py");
      print(test);
    } on PlatformException catch (e) {
      print('Error: ${e.code}\nError Message: ${e.message}');
    }
    setState(() {
      _test = test;
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(
          title: Text("PoC IoT - Récupération des données"),
        ),
        body: new Container(
          decoration: new BoxDecoration(
            image: new DecorationImage(
              image: new AssetImage("img/ciel.jpg"),
              fit: BoxFit.cover,
            ),
          ),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              TextButton(
                child: Image.asset('img/Prevention.jpg'),
                onPressed: () {
                  Navigator.push(
                    context,
                    MaterialPageRoute(builder: (BuildContext context) {
                      return Page3();
                    }),
                  );
                },
                //child : Icon(Icons.arrow_forward),
              ),

              Center(
                child: ElevatedButton(
                  onPressed: connexion,
                  child: Text("Connexion au dispositif"),
                ),
              ),
              Text(_test),
              Container(
                width: double.infinity,
                height: 10.0,
              ),
      ],
          ),
        ),
      ),
    );
  }
}
