const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');
const startButton = document.getElementById('startButton');
const countdownDisplay = document.getElementById('countdown');

// Game variables
let birdY = canvas.height / 2;
let birdSpeed = 0;
const birdSize = 40;
const gravity = 0.5;
const flapPower = -8;

const pipeWidth = 40;
const pipeGap = 200; // Increased pipe gap to make the game easier
let pipeX = canvas.width;
let pipeHeight = Math.floor(Math.random() * (canvas.height - pipeGap));

let score = 0;
let gameOver = false;
let gameStarted = false;

// Load the bird and pipe images
const birdImage = new Image();
const pipeImage = new Image();

// Flag to ensure the game starts only when images are fully loaded
let imagesLoaded = false;

// Load images from the directory
birdImage.src = 'images/bird.png';  // Path to bird image
pipeImage.src = 'images/pipe.png';  // Path to pipe image

// Event listeners to check when both images are loaded
birdImage.onload = checkImagesLoaded;
pipeImage.onload = checkImagesLoaded;

function checkImagesLoaded() {
  if (birdImage.complete && pipeImage.complete) {
    imagesLoaded = true;
  }
}

// Start button click event
startButton.addEventListener('click', () => {
  if (imagesLoaded) {
    startButton.style.display = 'none'; // Hide the start button
    startCountdown(); // Start the countdown
  } else {
    console.log('Images are still loading...');
  }
});

function startCountdown() {
  countdownValue = 3; // Reset countdown value
  drawCountdown(countdownValue);

  const countdownInterval = setInterval(() => {
    countdownValue--;
    if (countdownValue > 0) {
      drawCountdown(countdownValue);
    } else {
      clearInterval(countdownInterval);
      gameStarted = true;
      startGame();
    }
  }, 1000);
}

// Draw the countdown on the canvas
function drawCountdown(number) {
  drawGameElements(); // Continuously draw the game screen during the countdown
  ctx.fillStyle = 'rgba(255, 255, 255, 0.7)'; // Slightly transparent white background
  ctx.fillRect(0, 0, canvas.width, canvas.height); // Cover the canvas to dim it

  ctx.fillStyle = 'black';
  ctx.font = '40px Arial';
  ctx.textAlign = 'center';
  ctx.fillText(number, canvas.width / 2, canvas.height / 2);
}

// Listen for key presses only after the game has started
document.addEventListener('keydown', () => {
  if (gameStarted && !gameOver) {
    birdSpeed = flapPower;
  }
});

// Game loop
function gameLoop() {
  if (!gameOver && gameStarted) {
    // Clear canvas
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Bird movement
    birdSpeed += gravity;
    birdY += birdSpeed;

    // Pipe movement
    pipeX -= 1; // Reduced pipe speed to make the game easier
    if (pipeX + pipeWidth < 0) {
      pipeX = canvas.width;
      pipeHeight = Math.floor(Math.random() * (canvas.height - pipeGap));
      score++;
    }

    // Draw game elements
    drawGameElements();

    // Check for collision
    if (birdY + birdSize > canvas.height || birdY < 0 ||
        (50 < pipeX + pipeWidth && 50 + birdSize > pipeX &&
         (birdY < pipeHeight || birdY + birdSize > pipeHeight + pipeGap))) {
      gameOver = true;
      gameStarted = false;
      displayGameOver();
    }

    // Loop the game
    requestAnimationFrame(gameLoop);
  }
}

// Function to draw bird, pipes, and score
function drawGameElements() {
  // Clear canvas
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  // Draw bird (use custom image)
  ctx.drawImage(birdImage, 50, birdY, birdSize, birdSize);

  // Draw pipes (use custom image)
  ctx.drawImage(pipeImage, pipeX, 0, pipeWidth, pipeHeight);
  ctx.drawImage(pipeImage, pipeX, pipeHeight + pipeGap, pipeWidth, canvas.height - (pipeHeight + pipeGap));

  // Draw score
  ctx.fillStyle = 'black';
  ctx.font = '20px Arial';
  ctx.fillText('Score: ' + score, 10, 20);
}

// Start the game after the countdown
function startGame() {
  birdY = canvas.height / 2; // Reset bird position
  birdSpeed = 0; // Reset bird speed
  pipeX = canvas.width; // Reset pipe position
  score = 0; // Reset score
  gameOver = false; // Reset game over flag
  gameLoop(); // Start the game loop
}

// Display "Game Over" text
function displayGameOver() {
  ctx.fillStyle = 'red';
  ctx.font = '30px Arial';
  ctx.textAlign = 'center';
  ctx.fillText('Game Over', canvas.width / 2, canvas.height / 2);
}
