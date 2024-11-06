<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>DELETE METHODE</title>
    <style>
        .container{
			--max-width: 1000px;
			--padding: 1rem;

			width: min(var(--max-width), 100% - (var(--padding) * 1.2));
			margin-inline: auto;
		}
		body {
			display: flex;
			justify-content: center;
			align-items: center;
			height: 100vh;
			font-family: 'Inter', sans-serif;
			background-color: #faeedc;
		}
		div {
			font-size: 2rem;
			font-weight: semibold;
			color: #281515;
			text-align: center;
		}

		.button{
			margin-top: 2rem;
			border: none;
			padding: 1rem 3rem;
			background-color: #121212;
			border-radius: 15px;
			font-weight: semibold;
			color: white;
		}
        
        .button:hover{
            opacity: .9;
        }
    </style>
</head>
<body>
    <div class="container">
        <h2>Delete a Resource</h2>
        <form id="deleteForm">``
            <label for="resource">Select a resource to delete:</label>
            <select id="resource" name="resource">
                <?php
                // Définir le chemin vers le répertoire contenant les fichiers
                $directory = 'www/cgi-bin/uploads/'; // Assurez-vous que le dossier "files" existe et contient des fichiers .txt
    
                // Vérifiez si le répertoire existe
                if (is_dir($directory)) {
                    // Scannez le répertoire pour obtenir les fichiers
                    $files = scandir($directory);
    
                    // Parcourez les fichiers et affichez ceux avec l'extension .txt
                    foreach ($files as $file) {
                        // Filtrer les fichiers pour éviter les répertoires spéciaux comme "." et ".."
                        if ($file !== '.' && $file !== '..' && pathinfo($file, PATHINFO_EXTENSION) === 'txt') {
                            echo '<option value="' . $file . '">' . $file . '</option>';
                        }
                    }
                } else {
                    echo '<option value="">Répertoire introuvable</option>';
                }
                ?>
            </select>
            <br><br>
            <button type="button" class="button" onclick="deleteResource()">Delete</button>
        </form>
        <p id="responseMessage"></p>
    </div>
		<script src="https://cdn.jsdelivr.net/npm/js-confetti@latest/dist/js-confetti.browser.js"></script>

<script>
				const jsConfetti = new JSConfetti()
        function deleteResource() {
            console.log('Delete resource');
        }
    </script>
</body>
</html>