import os
import pathlib
import shutil  


with open('nim_list', 'r') as f:
    content = f.read()

    for nim in content.split('\n'):
        # if not os.path.exists(nim):
        #     os.mkdir(nim)
        
        # base_path = pathlib.Path(nim)

        # os.mkdir(base_path/"res")
        # os.mkdir(base_path/"src")
        # os.mkdir(base_path/"include")
        shutil.copytree('.template', nim)


    