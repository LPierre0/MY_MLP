import os
import shutil
import matplotlib.pyplot as plt
from skimage.transform import resize
import time
import glob

path_newFile = '/home/pierre/Documents/AI/DatasetCleaned/'

# Supprimer et recréer le dossier de destination
shutil.rmtree(path_newFile, ignore_errors=True)
os.makedirs(path_newFile)

def clear_terminal():
    # Clear the terminal screen
    os.system('cls' if os.name == 'nt' else 'clear')

path_dataset = '/home/pierre/Documents/AI/FirstNeuralNetwork/dataset'

if os.path.isdir(path_dataset):
    # Parcourir récursivement les fichiers dans le répertoire source
    for root, dirs, files in os.walk(path_dataset):
        for file in files:
            # Vérifier si le fichier est une image JPG ou PNG
            if file.lower().endswith(('.jpg', '.jpeg', '.png')):
                path_image = os.path.join(root, file)
                try:
                    # Charger l'image
                    img = plt.imread(path_image)
                    
                    # Redimensionner l'image
                    resize_img = resize(img, (800, 800), anti_aliasing=True)
                    
                    # Déterminer le dossier de destination
                    dest_folder = os.path.join(path_newFile, os.path.relpath(root, path_dataset))
                    
                    # Créer le dossier de destination si nécessaire
                    os.makedirs(dest_folder, exist_ok=True)
                    
                    # Enregistrer l'image redimensionnée
                    dest_file = os.path.join(dest_folder, file)
                    plt.imsave(dest_file, resize_img)
                    
                    print(f"Image {file} traitée avec succès.")
                except Exception as e:
                    print(f"Erreur lors du traitement de l'image {file}: {e}")
else:
    print("Le chemin spécifié n'existe pas ou n'est pas un répertoire.")
