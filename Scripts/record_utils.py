import time
import os
import obsws_python as obs

try:
    cl = obs.ReqClient(host="localhost", port=4455, password="")
except Exception as e:
    print(
        "Unable to connect to OBS Websockets. Make sure that OBS Studio is running > v28 and the webserver is enabled."
    )
    raise e

RECORD_DIR = os.path.join(os.path.dirname(__file__), "../", "RecordingSessions")  # r""
REFRESH_RATE = 0.25

print("Connected to OBS Studio Websockets API")

outputs = cl.get_output_list()
print("Available Outputs", outputs)

default_output_name = "simple_file_output"
print("Setting default output:", default_output_name)

if cl.get_record_status().output_active:
    cl.stop_record()

counter = 0
while True:
    files = new_files = set(os.listdir(RECORD_DIR))

    while files == new_files:
        new_files = set(os.listdir(RECORD_DIR))
        time.sleep(REFRESH_RATE)

        if counter > REFRESH_RATE * 100:
            print("Waiting for new capture to start...")
            counter = 0
        counter += 1

    new_file = list(new_files - files)[0]
    print("New File Created: ", new_file)

    new_mp4_file = new_file.replace("csv", "mp4")

    cl.set_output_settings(
        default_output_name, {"path": os.path.join(RECORD_DIR, new_mp4_file)}
    )

    print("Starting to Record OBS Video: ", new_mp4_file)
    cl.start_record()

    file_size = 0
    current_file_size = os.path.getsize(os.path.join(RECORD_DIR, new_file))

    while file_size != current_file_size:

        try:
            assert cl.get_record_status().output_active
        except:
            print("Recording was stopped")
            break

        file_size = os.path.getsize(os.path.join(RECORD_DIR, new_file))

        time.sleep(REFRESH_RATE)

        current_file_size = os.path.getsize(os.path.join(RECORD_DIR, new_file))

    cl.stop_record()
    print("Recording Finished.")
