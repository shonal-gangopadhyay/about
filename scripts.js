document.addEventListener("DOMContentLoaded", async () => {
    const blogContainer = document.getElementById("blog-container");

    async function fetchPosts() {
        try {
            const script = document.createElement("script");
            script.src = "posts/posts.js";
            script.onload = async () => {
                blogContainer.innerHTML = ""; // Clear loading text
                for (let postFile of posts) {
                    let postScript = document.createElement("script");
                    postScript.src = `posts/${postFile}`;
                    postScript.onload = () => {
                        let postData = window[postFile.replace(".js", "")]; // Get the post object
                        let postElement = document.createElement("div");
                        postElement.classList.add("blog-post");
                        postElement.innerHTML = `
                            <h3>${postData.title}</h3>
                            <small>${postData.date}</small>
                            <p>${postData.content}</p>
                            <hr>
                        `;
                        blogContainer.appendChild(postElement);
                    };
                    document.body.appendChild(postScript);
                }
            };
            document.body.appendChild(script);
        } catch (error) {
            blogContainer.innerHTML = "<p>Failed to load blog posts.</p>";
            console.error("Error loading posts:", error);
        }
    }

    fetchPosts();
});
