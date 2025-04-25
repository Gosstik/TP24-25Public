FROM python:3.10

COPY . /app/

WORKDIR /app

RUN pip3 install -r requirements.txt

# ENTRYPOINT python3 app.py --host localhost --port 8898
# ENTRYPOINT python3 app.py --host 0.0.0.0 --port 8898
ENTRYPOINT ["python3", "app.py", "--host", "0.0.0.0", "--port", "8898"]

EXPOSE 8898
