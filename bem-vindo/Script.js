// Aguarde 2 segundos e comece a desaparecer a imagem
setTimeout(() => {
  const splashScreen = document.querySelector('.splash-screen');
  splashScreen.style.opacity = 0;
  setTimeout(() => {
    splashScreen.style.display = 'none';
    document.querySelector('.desktop').style.display = 'block';
  }, 2000); // Aguarde 2 segundos para a transição de opacidade
}, 2000);
