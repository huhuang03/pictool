import os

CUR_FILE_DIR = os.path.dirname(__file__)
LINK_PATH = os.path.join(CUR_FILE_DIR, '../external/easybot')
print(os.path.realpath(LINK_PATH))
print(LINK_PATH)
# LINK_PATH = os.path.join(__FILE, )
# os.path.realpath()