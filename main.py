from googletrans import Translator
from http.server import BaseHTTPRequestHandler, HTTPServer

translator = Translator(service_urls=['translate.googleapis.com'])

hostName = "tiny-morse-translate.vercel.app"
serverPort = 80

class MyServer(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode()
        translated = translator.translate(post_data, dest='en', src="de")
        print(post_data, translated.text)

        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(translated.text.encode())

    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write("make a post request".encode())

if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")