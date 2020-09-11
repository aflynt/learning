
# secure the server
  # turn off pss login
  vim /etc/ssh/sshd_config
    * set
    PasswordAuthentication no
  
  # restart the ssh deamon
  system ctl restart sshd
  
  
  # get uncomplicated firewall
  sudo apt install ufw
  
  sudo ufw default allow outgoing
  sudo ufw default deny incoming
  
  # allow for ssh and tcp
  sudo ufw allow ssh
  
  # allow port 5000
  sudo ufw allow 5000
  
  # dont allow http and port 80 traffice
  
  sudo ufw enable
  
  
  sudo ufw status

# push app to server
  pip freeze > requirements.txt

  scp -r Desktop/Flask_Blog coreyms@ip:~/

# install dependencies

  sudo apt install python3-pip
  sudo apt install python3-venv

  # create a virtual environment
  python3 -m venv Flask_Blog/venv

  source venv/bin/activate

  pip install -r requirements.txt

# get environment variables  
  python
  import os
  os.environ.get('SECRET_KEY')
  os.environ.get('SQLALCHEMY_DATABASE_URI')
  os.environ.get('EMAIL_USER')
  os.environ.get('EMAIL_PASS')

# app config
  sudo touch /etc/config.json
  {
    "SECRET_KEY": "xxx",
    "SQL...": "yyy",
  }

# run the app
  export FLASK_APP=run.py
  flask run --host=0.0.0.0

  # go to IP ADDRESS
  ip:5000

# use enginex and gunicorn to run faster
  sudo apt install enginex
  pip install gunicorn



