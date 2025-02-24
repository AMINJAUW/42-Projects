import time
import sys
import os

# Get the environment variable HTTP_SCRIPT_TIME and set the wait time accordingly
wait_time = float(os.getenv('HTTP_SCRIPT_TIME', 0))

# Sleep for the specified time
time.sleep(wait_time)

# Create the response
html_content = '''<html>
<head><title>CGI Example</title></head>
<body>
<h1>CGI Example</h1>
<p>This script waited {} seconds</p>
</body>
</html>'''.format(wait_time)

# Generate CGI headers
content = html_content.encode('utf-8')
content_length = len(content) + 1
print("Content-Type: text/html")
print("Content-Length: {}".format(content_length))
print()
print(html_content)
