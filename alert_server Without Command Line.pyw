from http.server import BaseHTTPRequestHandler, HTTPServer
from pygame import mixer 



class HttpProcessor(BaseHTTPRequestHandler):
    def do_GET(self):
        if(self.headers["User-Agent"]=="ESP8266HTTPClient"):
            if(self.path == "/voice_alert"):
                voiceAlert()
            elif(self.path == "/door_alert"):
                doorAlert()
        self.send_response(200)

def voiceAlert():
    mixer.init()
    print("alert")
    path = 'C:/Users/storm/Documents/alarm/voice_alert.mp3'
    mixer.music.load(path)
    mixer.music.play()


def doorAlert():
    mixer.init()
    print("\nALERT!!!!!!!!!!!!!!!!!!\n\n""ALERT!!!!!!!!!!!!!!!!!!\n\n""ALERT!!!!!!!!!!!!!!!!!!\n")
    path = 'C:/Users/storm/Documents/alarm/door_alert.mp3'
    mixer.music.load(path)
    mixer.music.play()

serv = HTTPServer(("192.168.1.51",9090),HttpProcessor)

try:
    serv.serve_forever()
except KeyboardInterrupt:
    pass