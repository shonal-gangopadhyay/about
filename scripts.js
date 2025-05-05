function checkPassword() {
    var password = prompt("Enter the password to access this page:");
    var correctPassword = "shonalshonal";  // Change this to your actual password

    if (password === correctPassword) {
        window.location.href = "about/about-personal.html";  // Change this to your actual secret page
    } else if (password !== null) {
        alert("Incorrect password. Ask me if you need the password.");
    }
}

document.addEventListener("DOMContentLoaded", async () => {
    const blogContainer = document.getElementById("blog-container");

    function loadScript(url) {
        return new Promise((resolve, reject) => {
            const script = document.createElement("script");
            script.src = url;
            script.onload = resolve;
            script.onerror = reject;
            document.body.appendChild(script);
        });
    }

    async function fetchPosts() {
        try {
            await loadScript("posts/posts.js"); // ✅ Load posts.js first

            blogContainer.innerHTML = ""; // Clear "Loading posts..."
            for (let postFile of window.posts) {
                await loadScript(`posts/${postFile}`); // ✅ Load each post

                let postVarName = postFile.replace(".js", ""); // Get variable name
                let postData = window[postVarName]; // ✅ Get post data

                if (postData) {
                    let postElement = document.createElement("div");
                    postElement.classList.add("blog-post");
                    postElement.innerHTML = `
                        <h3>${postData.title}</h3>
                        <small>${postData.date}</small>
                        <p>${postData.content}</p>
                        <hr>
                    `;
                    blogContainer.appendChild(postElement);
                } else {
                    console.error(`Post data not found for ${postVarName}`);
                }
            }
        } catch (error) {
            blogContainer.innerHTML = "<p>Failed to load blog posts.</p>";
            console.error("Error loading posts:", error);
        }
    }

    fetchPosts();
});




