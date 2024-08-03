#ifndef HANDLERCONST_HPP
#define HANDLERCONST_HPP

#include <string>

const std::string HOMEPAGE_1 = R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home</title>
    <style>
        body {
            margin: 0;
            padding: 0;
            font-family: Arial, sans-serif;
            background-color: #000911;
        }

        .container {
            max-width: 1000px;
            color: #dedede;
            margin: 60px auto 20px;
            background-color: #020b1b;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
            position: relative;
            padding: 20px;
            padding-top: 80px;
        }

        header {
            background-color: #3498db;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 10px 20px;
            flex-wrap: wrap;
        }

        .profile-photo {
            width: 120px;
            height: 120px;
            border-radius: 50%;
            position: absolute;
            object-fit: cover;
            top: -60px;
            left: 20px;
            border: 5px solid #020b1b;
        }

        @media only screen and (max-width: 600px) {
            .container {
                padding: 10px;
                margin: 10px;
                padding-top: 60px;
            }

            .profile-photo {
                width: 80px;
                height: 80px;
                top: -40px;
            }

            .post {
                padding: 5px;
            }

            .post-photo {
                max-width: 100%;
            }

            .header-links ul li {
                display: block;
                margin: 10px 0;
            }
        }

        .post {
            margin-top: 20px;
            padding: 10px;
            background-color: #020116;
            border: 1px solid #aaa;
            border-radius: 4px;
        }

        .search-box {
            position: relative;
            display: flex;
            align-items: center;
            margin-left: 10px;
        }

        .search-box input {
            width: 200px;
            padding: 10px 40px 10px 20px; /* Adjust padding to make room for the button */
            border-radius: 20px;
            border: 1px solid #ccc;
            outline: none;
            transition: all 0.3s ease;
        }

        .search-box input:focus {
            border-color: #3498db;
            box-shadow: 0 0 8px rgba(52, 152, 219, 0.5);
        }

        .search-box button {
            position: absolute;
            right: 5px;
            top: 50%;
            transform: translateY(-50%);
            padding: 5px 10px;
            border: none;
            background-color: #3498db;
            color: white;
            border-radius: 20px;
            cursor: pointer;
            transition: background-color 0.3s ease;
        }

        .search-box button:hover {
            background-color: #2980b9;
        }

        .search-box button:focus {
            outline: none;
        }


        .logout-button {
            padding: 5px 10px;
            border: none;
            background-color: #030000;
            color: #c4c7c9;
            border-radius: 20px;
            cursor: pointer;
        }

        .logo {
            width: 40px;
            height: auto;
        }

        .header-links ul {
            list-style-type: none;
            padding: 0;
            margin: 0;
            display: flex;
        }

        .header-links ul li {
            margin-right: 10px;
        }

        .header-links ul li a {
            text-decoration: none;
            color: #fff;
            padding: 1px;
            transition: color 0.3s;
        }

        .header-links ul li a:hover {
            color: #000000;
        }

        .post-photo {
            max-width: 100%;
            height: auto;
            border-radius: 4px;
            margin-top: 10px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
        }

        .form-content {
            display: flex;
            align-items: center;
        }

        .bodypage {
            padding-top: 30px;
        }

        .personal-info {
            padding-left: 10px;
        }

        .header-right {
            align-items: center;
            display: flex;
            align-items: self-end;
        }

        .header-links {
            display: flex;
            justify-content: center;
            padding-bottom: 10px;
            padding-right: 10px;
        }
    </style>
</head>

<body>
    <header>
        <div class="form-content">
            <form action="/logout" method="post">
                <button type="submit" class="logout-button">Logout</button>
            </form>
            <div class="search-box">
                <form id="search-form" action="/search" method="GET">
                    <input type="text" name="query" placeholder="Search personal pages">
                    <button type="submit">Search</button>
                </form>
            </div>
        </div>
        <div class="header-right">
            <div class="header-links">
                <ul>)";

const std::string HOMEPAGE_2 = R"(<li><a href="/ShowCourses" id= "show-courses-link">Show Courses</a></li>
                    <li><a href="/ChangeProfile" id="show-change-profile-link">Change Profile</a></li>
                    <li><a href="/Post" id="show-send-post-link">Post</a></li></ul>
            </div>
            <img src="UT_Mark.png" class="logo" alt="Logo">
        </div>
    </header>
    <div class="bodypage" >
    <div class="container">)";

const std::string HOMEPAGE_3 = R"(    </div></div>
    <script>
        const profilePhoito = document.getElementById('profile-photo');
        profilePhoto.addEventListener('click', () => {
            console.log('Profile photo clicked!');
        });

        const changeProfileLink = document.getElementById('show-change-profile-link');
        changeProfileLink.addEventListener('click', (e) => {
            e.preventDefault();
            changeProfile();
        });

        function changeProfile() {
            fetch('/changeProfile', {
                method: 'POST',
                headers: {
                    'Content-Type': 'text/html'
                }
            })
            .then(response => {
                if (response.ok) {
                    return response.text();
                } else {
                    throw new Error('Network response was not ok.');
                }
            })
            .then(data => {
                console.log('Success:', data);
                displayCourses(data);
            })
            .catch(error => {
                console.error('Error:', error);
            });
        }

        const sendPostLink = document.getElementById('show-send-post-link');
        sendPostLink.addEventListener('click', (e) => {
            e.preventDefault();
            sendPost();
        });

        function sendPost() {
            fetch('/sendPost', {
                method: 'POST',
                headers: {
                    'Content-Type': 'text/html'
                }
            })
            .then(response => {
                if (response.ok) {
                    return response.text();
                } else {
                    throw new Error('Network response was not ok.');
                }
            })
            .then(data => {
                console.log('Success:', data);
                displayCourses(data);
            })
            .catch(error => {
                console.error('Error:', error);
            });
        }

        const showCoursesLink = document.getElementById('show-courses-link');
        showCoursesLink.addEventListener('click', (e) => {
            e.preventDefault();
            showCourses();
        });

        function showCourses() {
            fetch('/showCourses', {
                method: 'POST',
                headers: {
                    'Content-Type': 'text/html'
                }
            })
            .then(response => {
                if (response.ok) {
                    return response.text();
                } else {
                    throw new Error('Network response was not ok.');
                }
            })
            .then(data => {
                console.log('Success:', data);
                displayCourses(data);
            })
            .catch(error => {
                console.error('Error:', error);
            });
        }
        
        const offerCourseLink = document.getElementById('offer-course-link');
        offerCourseLink.addEventListener('click', (e) => {
            e.preventDefault();
            offerCourse();
        });

        function offerCourse() {
            fetch('/offerCourse', {
                method: 'POST',
                headers: {
                    'Content-Type': 'text/html'
                }
            })
            .then(response => {
                if (response.ok) {
                    return response.text();
                } else {
                    throw new Error('Network response was not ok.');
                }
            })
            .then(data => {
                console.log('Success:', data);
                displayCourses(data);
            })
            .catch(error => {
                console.error('Error:', error);
            });
        }

        const myCoursesLink = document.getElementById('my-courses-link');
        myCourseLink.addEventListener('click', (e) => {
            e.preventDefault();
            myCourses();
        });

        function myCourses() {
            fetch('/myCourses', {
                method: 'POST',
                headers: {
                    'Content-Type': 'text/html'
                }
            })
            .then(response => {
                if (response.ok) {
                    return response.text();
                } else {
                    throw new Error('Network response was not ok.');
                }
            })
            .then(data => {
                console.log('Success:', data);
                displayCourses(data);
            })
            .catch(error => {
                console.error('Error:', error);
            });
        }

    </script>
</body>

</html>)";

const std::string POST_BOX = R"(<!DOCTYPE html>
<html lang="en">

<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Create a Post</title>
<style>
    body {
        background-color: #030000;
        font-family: Arial, sans-serif;
    }

    .container {
        max-width: 600px;
        margin: 20px auto;
        padding: 20px;
        padding-right: 35px;
        background-color: rgb(252, 252, 253);
        border-radius: 10px;
        box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
    }

    h1 {
        color: #333;
    }

    form input,
    form textarea {
        width: 100%;
        padding: 8px;
        margin-bottom: 10px;
        border: 1px solid #ccc;
        border-radius: 4px;
    }

    button {
        padding: 8px 16px;
        background-color: #3498db;
        color: white;
        border: none;
        border-radius: 4px;
        cursor: pointer;
    }

    button:hover {
        background-color: #2980b9;
    }
    
</style>
</head>

<body>
    <div class="container">
        <h1>Create a Post</h1>
        <form action="/CreatePost" method="post" enctype="multipart/form-data">
            <label for="title">Title:</label><br>
            <input type="text" id="title" name="title" required><br><br>

            <label for="message">Message:</label><br>
            <textarea id="message" name="message" rows="5" required></textarea><br><br>

            <label for="image">Choose an image:</label><br>
            <input type="file" id="image" name="image"><br><br>

            <button type="submit">Post</button>
        </form>
    </div>
</body>

</html>)";

const std::string CHANGE_PROFILE_BOX_1 = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Profile Photo</title>
    <style>
        body, html {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Arial', sans-serif;
            background: #020b1b;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .container {
            background: #020d20;
            padding: 20px;
            border-radius: 15px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            text-align: center;
            transition: transform 0.3s ease, box-shadow 0.3s ease;
        }

        .container:hover {
            transform: translateY(-5px);
            box-shadow: 0 8px 16px rgba(0, 0, 0, 0.2);
        }

        .profile-photo-section {
            position: relative;
        }

        #profile-photo {
            width: 150px;
            height: 150px;
            border-radius: 50%;
            object-fit: cover;
            border: 5px solid #ddd;
            transition: border-color 0.3s ease;
        }

        .profile-photo-section:hover #profile-photo {
            border-color: #dedede;
        }

        .buttons {
            margin-top: 15px;
            display: flex;
            align-items: self-end;
        }

        .btn {
            background: #007bff;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 25px;
            cursor: pointer;
            transition: background 0.3s ease;
            margin: 5px;
        }

        .btn:hover {
            background: #0056b3;
        }

        #fileInput {
            display: none;
        }
    </style>
</head>
<body>
    <div class="container">
<div class="profile-photo-section">)";

const std::string CHANGE_PROFILE_BOX_2 = R"(
            <div class="buttons">
                <form id="profileForm" action="/addProfile" method="post" enctype="multipart/form-data">
                    <input type="file" id="fileInput" name="image" )";
const std::string CHANGE_PROFILE_BOX_3 = R"(onchange="handleFileChange(this))";
const std::string CHANGE_PROFILE_BOX_4 = R"(">
                    <button type="button" class="btn" onclick="document.getElementById('fileInput').click();">Change Photo</button>
                    <button type="submit" class="btn" id="submitBtn" style="display: none;">Upload Photo</button>
                </form>
                <form action="/DeleteProfile" method="post">
                    <button class="btn" id="delete-photo">Delete Photo</button>
                </form>
        </div>
    </div>

    <script>
        function handleFileChange(input) {
            var fileName = input.files[0].name;
            var uploadButton = document.getElementById('submitBtn');


            document.getElementById('profileForm').submit();
        }

        document.getElementById('delete-photo').addEventListener('click', () => {
            document.getElementById('profile-photo').src = 'NOT_ENTERED.png';
        });
    </script>
</body>
</html>
)";

const std::string SHOW_COURSE_PAGE_1 = R"(<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>University Courses</title>
    <style>
        body {
            margin: 0;
            padding: 0;
            font-family: 'Arial', sans-serif;
            background-color: #0d1b2a;
            color: #ffffff;
            overflow-x: hidden;
        }

        header {
            background-color: #0d1b2a;
            padding: 20px;
            display: flex;
            justify-content: center;
            align-items: center;
        }

        .logo {
            border-radius: 50%;
            width: 100px;
            height: auto;
            box-shadow: 0 2px 4px rgba(4, 4, 4, 8);
        }

        .container {
            max-width: 1200px;
            margin: 20px auto;
            padding: 20px;
            background-color: #1b263b;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.3);
        }

        h1 {
            text-align: center;
            margin-bottom: 20px;
        }

        .courses-container {
            display: flex;
            flex-wrap: wrap;
            gap: 20px;
            justify-content: center;
            opacity: 0;
            transform: translateY(20px);
            animation: fadeInUp 1s forwards;
        }

        .course-card {
            background-color: #2e3a59;
            border-radius: 8px;
            padding: 20px;
            width: 300px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            transition: transform 0.3s;
        }

        .course-card:hover {
            transform: scale(1.05);
        }

        .home-button {
            background-color: #1f1f20;
            color: #ebebeb;
            padding: 10px 20px;
            border: none;
            border-radius: 16px;
            font-size: 1em;
            cursor: pointer;
            transition: background-color 0.3s;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            display: block;
            margin: 30px auto;
        }

        .home-button:hover {
            background-color: #000000;
            transform: scale(1.05);
        }

        .course-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 10px;
            padding-bottom: 20px;
        }

        .course-id {
            font-size: 0.9em;
            color: #a9bcd0;
            padding-right: 12px;
        }

        .course-name {
            font-size: 1.2em;
            font-weight: bold;
            color: #e0e1dd;
        }

        .course-details {
            font-size: 0.9em;
            margin: 5px 0;
            color: #a9bcd0;
        }

        @keyframes fadeInUp {
            to {
                opacity: 1;
                transform: translateY(0);
            }
        }

                .no-courses {
            text-align: center;
            font-size: 1.2em;
            color: #a9bcd0;
            margin-top: 20px;
        }
    </style>
</head>

<body>
    <header>
        <img src="UT_Mark.png" alt="University Logo" class="logo">
    </header>
    <div class="container">
        <h1>Courses Offered</h1>
        <div class="courses-container">)";
const std::string SHOW_COURSE_PAGE_2 = R"(</div>
        </div>
        <div class="no-courses">There are no courses offered yet.</div>
        <button class="home-button" onclick="location.href='/home'">Home</button>
    <script>
        document.addEventListener('DOMContentLoaded', () => {
            const coursesContainer = document.querySelector('.courses-container');
            coursesContainer.style.opacity = 1;
            coursesContainer.style.transform = 'translateY(0)';
        });

        document.addEventListener('DOMContentLoaded', () => {
            const coursesContainer = document.querySelector('.courses-container');
            const noCoursesMessage = document.querySelector('.no-courses');
            if (coursesContainer.children.length === 0) {
                noCoursesMessage.style.display = 'block';
            } else {
                noCoursesMessage.style.display = 'none';
                coursesContainer.style.opacity = 1;
                coursesContainer.style.transform = 'translateY(0)';
            }
        })
    </script>
</body>

</html>
)";

const std::string COURSE_OFFER_1 = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Offer a Course</title>
    <style>
        /* Reset and global styles */
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }

        body {
            font-family: Arial, sans-serif;
            background-color: #1a1a1a;
            color: #ffffff;
            line-height: 1.6;
            padding-bottom: 100px;
        }

        .container {
            width: 80%;
            margin: 0 auto;
            padding: 20px 0;
        }

        header {
            background-color: #1a1a1a;
            text-align: center;
        }

        header img {
            max-width: 200px;
            border-radius: 50%;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2);
        }

        .main {
            padding: 10px 0;
            text-align: center;
        }

        h1 {
            font-size: 2.5em;
            margin-bottom: 20px;
        }

        .course-container {
            position: relative;
        }

        .loading-spinner {
            position: absolute;
            top: 50%;
            left: 50%;
            width: 50px;
            height: 50px;
            margin: -25px 0 0 -25px;
            border: 6px solid #333333;
            border-top: 6px solid #3e98b6;
            border-radius: 50%;
            animation: spin 1s linear infinite;
        }

        @keyframes spin {
            0% { transform: rotate(0deg); }
            100% { transform: rotate(360deg); }
        }

        .course-form {
            max-width: 600px;
            margin: 0 auto;
            background-color: #333333;
            padding: 30px;
            border-radius: 8px;
            box-shadow: 0 0 20px rgba(0, 0, 0, 0.2);
            opacity: 0;
            transform: translateY(20px);
            transition: opacity 0.5s ease-in-out, transform 0.5s ease-in-out;
        }

        .course-form.loaded {
            opacity: 1;
            transform: translateY(0);
        }

        form label {
            display: block;
            margin-bottom: 8px;
        }


        form input, form button, form select {
            width: calc(100% - 20px);
            padding: 10px;
            margin-bottom: 15px;
            border: none;
            background-color: #555555;
            color: #ffffff;
            border-radius: 4px;
        }

        form input, form button {
            width: calc(100% - 20px);
            padding: 10px;
            margin-bottom: 15px;
            border: none;
            background-color: #555555;
            color: #ffffff;
            border-radius: 4px;
        }

        form button {
            background-color: #3e98b6;
            cursor: pointer;
            transition: background-color 0.3s ease;
        }

        form button:hover {
            background-color: #3e74b6;
        }

        footer {
            background-color: #1a1a1a;
            text-align: center;
            padding: 10px 0;
            position: fixed;
            bottom: 0;
            width: 100%;
        }
    </style>
</head>
<body>
    <header>
        <div class="container">
            <img src="UT_Mark.png" alt="University Logo" class="logo">
        </div>
    </header>

    <section class="main">
        <div class="container">
            <h1>Offer a Course</h1>
            <div class="course-container">
                <div class="loading-spinner" id="loadingSpinner"></div>
                <div class="course-form" id="courseForm">
                    <form action="/offerNewCourse" method="post"  enctype="multipart/form-data">
                        <label for="courseId">Course Id:</label>
                        <input type="text" id="courseId" name="courseId" required>

                        <label for="professorId">Professor Id:</label>
                        <input type="text" id="professorId" name="professorId" required>
                        
                        <label for="capacity">Capacity:</label>
                        <input type="number" id="capacity" name="capacity" required>
                        
                        <label for="examDate">Exam Date:</label>
                        <input type="date" id="examDate" name="examDate" required>
                        
                        <label for="day">Class Day:</label>
                            <select id="day" name="day" required>
                                <option value="" disabled selected>Select a day</option>
                                <option value="Monday">Monday</option>
                                <option value="Tuesday">Tuesday</option>
                                <option value="Wednesday">Wednesday</option>
                                <option value="Saturday">Saturday</option>
                                <option value="Sunday">Sunday</option>
                            </select>

                        <label for="Time">Class Time:</label>
                        <input type="text" id="Time" name="Time" pattern="(?:[01]\d|2[0123])-(?:[012345]\d))";
const std::string COURSE_OFFER_2 = R"("title="Enter a valid 24-hour time (HH-MM))";
const std::string COURSE_OFFER_3 = R"("placeholder="HH-MM" required>
                        
                        <label for="classNumber">Class Number:</label>
                        <input type="text" id="classNumber" name="classNumber" required>
                        
                        <button type="submit">Offer Course</button>
                    </form>
                </div>
            </div>
        </div>
    </section>

    <footer>
        <div class="container">
            &copy; 2024 University Of Tehran. All rights reserved.
        </div>
    </footer>

    <script>
        document.addEventListener('DOMContentLoaded', function() {
            const spinner = document.getElementById('loadingSpinner');
            const form = document.getElementById('courseForm');

            // Simulate loading process
            setTimeout(function() {
                spinner.style.display = 'none';
                form.classList.add('loaded');
            }, 2000); // 2 seconds loading time
        });
    </script>
</body>
</html>)";

const std::string MY_COURSE_PAGE_1 = R"(<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>University Courses</title>
    <style>
        body {
            margin: 0;
            padding: 0;
            font-family: 'Arial', sans-serif;
            background-color: #0d1b2a;
            color: #ffffff;
            overflow-x: hidden;
        }

        header {
            background-color: #0d1b2a;
            padding: 20px;
            display: flex;
            justify-content: center;
            flex-direction: column;
            padding: 20px;
            align-items: center;
        }

        .logo {
            width: 150px;
            height: 150px;
            border-radius: 50%;
            object-fit: cover;
            border: 5px solid #ddd;
            transition: border-color 0.3s ease;
        }

        .container {
            max-width: 1200px;
            margin: 20px auto;
            padding: 20px;
            background-color: #1b263b;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.3);
        }

        h1 {
            text-align: center;
            margin-bottom: 20px;
        }

        .courses-container {
            display: flex;
            flex-wrap: wrap;
            gap: 20px;
            justify-content: center;
            opacity: 0;
            transform: translateY(20px);
            animation: fadeInUp 1s forwards;
        }

        .course-card {
            background-color: #2e3a59;
            border-radius: 8px;
            padding: 20px;
            width: 300px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            transition: transform 0.3s;
        }

        .course-card:hover {
            transform: scale(1.05);
        }

        .home-button {
            background-color: #1f1f20;
            color: #ebebeb;
            padding: 10px 20px;
            border: none;
            border-radius: 16px;
            font-size: 1em;
            cursor: pointer;
            transition: background-color 0.3s;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            display: block;
            margin: 30px auto;
        }

        .home-button:hover {
            background-color: #000000;
            transform: scale(1.05);
        }

        .course-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 10px;
            padding-bottom: 20px;
        }

        .course-id {
            font-size: 0.9em;
            color: #a9bcd0;
            padding-right: 12px;
        }

        .course-name {
            font-size: 1.2em;
            font-weight: bold;
            color: #e0e1dd;
        }

        .course-details {
            font-size: 0.9em;
            margin: 5px 0;
            color: #a9bcd0;
        }

        @keyframes fadeInUp {
            to {
                opacity: 1;
                transform: translateY(0);
            }
        }

        .no-courses {
            text-align: center;
            font-size: 1.2em;
            color: #a9bcd0;
            margin-top: 20px;
        }

        .btn {
            background: #007bff;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 25px;
            cursor: pointer;
            transition: background 0.3s ease;
            margin: 5px;
        }

        .btn:hover {
            background: #0056b3;
        }

        .delete-button {
            align-items: center;
            display: flex;
            padding-left: 85px;
        }

        .buttons {
            margin-bottom: 20px;
            display: flex;
            justify-content: first baseline;
            padding: 25px;
        }

        form input, form button {
        width: calc(100% - 20px);
        padding: 10px;
        margin-bottom: 15px;
        border: none;
        background-color: #555555;
        color: #ffffff;
        border-radius: 4px;
        }

        .btn {
        padding: 10px 20px;
        margin: 0 10px;
        border: none;
        background-color: #007bff;
        color: white;
        cursor: pointer;
        border-radius: 15px;
        font-size: 16px;
        }

        .Add-course{
          padding-right: 5px;
        }

        .Delete-course{
          padding-left: 5px;
        }
    </style>
</head>

<body>
    <header>
        <img src=")";
const std::string MY_COURSE_PAGE_2 = R"(" alt="Profile Logo" class="logo">
        <div class="buttons">
          <form action="/AddCourse" method="post" class="Add-course">
            <input type="number" name="courseId">
            <button class="btn" type="submit"><i class="fas fa-plus"></i> Register</button>
          </form>
          <form action="/DeleteCourse" method="post" class="Delete-course">
            <input type="number" name="courseId">
            <button class="btn" type="submit"><i class="fas fa-trash"></i> Delete</button>
          </form>
        </div>
    </header>
    <div class="container">
        <h1>My Courses</h1>
        <div class="courses-container">)";
const std::string MY_COURSE_PAGE_3 = R"(</div>
        </div>
        <div class="no-courses">You Have Not Any courses yet.</div>
        <button class="home-button" onclick="location.href='/home'">Home</button>
    <script>
        document.addEventListener('DOMContentLoaded', () => {
            const coursesContainer = document.querySelector('.courses-container');
            coursesContainer.style.opacity = 1;
            coursesContainer.style.transform = 'translateY(0)';
        });

        document.addEventListener('DOMContentLoaded', () => {
            const coursesContainer = document.querySelector('.courses-container');
            const noCoursesMessage = document.querySelector('.no-courses');
            if (coursesContainer.children.length === 0) {
                noCoursesMessage.style.display = 'block';
            } else {
                noCoursesMessage.style.display = 'none';
                coursesContainer.style.opacity = 1;
                coursesContainer.style.transform = 'translateY(0)';
            }
        })
    </script>
</body>

</html>
)";

#endif // HANDLERCONST_HPP