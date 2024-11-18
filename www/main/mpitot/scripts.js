// Scroll Animation
const sections = document.querySelectorAll('.about, .projects, .contact');

function checkVisibility() {
    sections.forEach(section => {
        const sectionTop = section.getBoundingClientRect().top;
        const sectionBottom = section.getBoundingClientRect().bottom;
        const triggerPoint = window.innerHeight / 1.2;

        if (sectionTop < triggerPoint && sectionBottom > 0) {
            section.classList.add('visible');  // Fade in when scrolling down
        } else {
            section.classList.remove('visible');  // Fade out when scrolling up
        }
    });
}

window.addEventListener('scroll', checkVisibility);
