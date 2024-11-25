#!/usr/bin/env python3

import cgi
import os
from pathlib import Path


# Créer une instance FieldStorage
form = cgi.FieldStorage()

# Récupérer les données du formulaire
filename = form.getvalue("filename")
content = form.getvalue("content")

# Chemin où le fichier sera créé
directory = "./www/main/cgi-bin/uploads/"
filepath = os.path.join(directory, filename)

file = Path(filepath)

print("Content-Type: text/html; charset=utf-8\r\n\r\n")  # En-tête HTTP

# si le fichier n'existe pas
if (file.exists()):
	value = f"Le fichier '{filename}' existe déjà."
else:
	# Initialiser la variable pour le contenu HTML
	value = ""

	# Vérifier si le répertoire existe, sinon le créer
	if not os.path.exists(directory):
			os.makedirs(directory)

	try:
			with open(filepath, "w") as file:
					file.write(content)
			value = f"Le fichier '{filename}' a été créé avec succès."

	except Exception as e:
			value = f"Échec de la création du fichier '{filename}'"

html_content = f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Informations de l'Utilisateur</title>
    <style>
    		.container{{
			--max-width: 1000px;
			--padding: 1rem;

			width: min(var(--max-width), 100% - (var(--padding) * 1.2));
			margin-inline: auto;
			}}
		body {{
			display: flex;
			justify-content: center;
			align-items: center;
			height: 100vh;
			font-family: 'Inter', sans-serif;
			background-color: #faeedc;
		}}
		div {{
			font-size: 2rem;
			font-weight: semibold;
			color: #281515;
			text-align: center;
		}}
</style>
</head>
<body>
    <div class="container">
        {value}
    </div>
</body>
</html>
"""

print(html_content)
