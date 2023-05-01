This python script will watch for any new files that are created in the RecordingSessions folder. When it sees a new file it will send a signal to OBS studio to start recording the current scene. When the file size stops changing, it will send a signal to OBS Studio to stop recording the current scene.

# OBS Studio Setup

    1. Download and install OBS Studio > 28.0
    2. Start OBS Studio
    3. Go to tools -> websocket server settings
    4. Enable the webserver and set a password

# Running the Python Script

    pip install obsws-python

    cd <this-directory>

    python record_utils.py
