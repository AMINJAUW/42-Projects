import sys

# Read data from stdin
post_data = sys.stdin.read()

# Create the response
html_content = '''<html>
<head><title>CGI Example</title></head>
<body>
<h1>CGI Example</h1>
<p>POST Data: {}</p>
</body>
</html>'''.format(post_data)

# Generate CGI headers
content = html_content.encode('utf-8')
content_length = len(content) + 1
print("Content-Type: text/html")
print("Content-Length: {}".format(content_length))
print()
print(html_content)
