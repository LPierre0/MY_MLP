import os
import matplotlib.pyplot as plt

path_dataset = '/home/pierre/Documents/AI/DatasetCleaned'

os.environ["XDG_SESSION_TYPE"] = "xcb"

fichiers = os.listdir(path_dataset)
for filename in fichiers: 
    dossier = os.listdir(f"{path_dataset}/{filename}")
    for image in dossier:
            path_image = f"{path_dataset}/{filename}/{image}"
            img = plt.imread(path_image)
            print(img.shape)