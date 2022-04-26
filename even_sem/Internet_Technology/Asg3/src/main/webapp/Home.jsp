<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
	<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
		<html>

		<head>
			<title>Travel Thru Air</title>
			<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
				integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T"
				crossorigin="anonymous">
		</head>

		<body>

			<header>
				<nav class="navbar navbar-expand-md navbar-dark" style="background-color: #332e2a">
					<div>
						<a href="/UserManagement" class="navbar-brand"> Travel Thru Air </a>
					</div>

					<ul class="navbar-nav ml-auto">
						<li><a href="<%=request.getContextPath()%>/list" class="nav-link">Flights</a></li>
						<li><a href="<%=request.getContextPath()%>/login" class="nav-link">Admin</a></li>
					</ul>
				</nav>
			</header>

			<div class="landing-page"
				style="background: white url('https://images.pexels.com/photos/46148/aircraft-jet-landing-cloud-46148.jpeg?auto=compress&cs=tinysrgb&dpr=2&h=650&w=940') no-repeat scroll center; background-size: cover; height: 100vh; color: #c8cfcf;">
				<div class="wrapper" style="background-color: rgba(0,0,0,0.7); height: 100%">

					<div class="d-flex flex-column justify-content-center align-items-center text-center h-100">
						<h5 class="display-4 zoomIn animate-charcter">WELCOME TO THE
							<br>
							<strong>Travel Thru Air</strong>
						</h5>
						<style>
							.animate-charcter {
								text-transform: uppercase;
								background-image: linear-gradient(-225deg,
										#231557 0%,
										#44107a 29%,
										#ff1361 67%,
										#fff800 100%);
								background-size: auto auto;
								background-clip: border-box;
								background-size: 200% auto;
								color: #fff;
								background-clip: text;
								-webkit-background-clip: text;
								-webkit-text-fill-color: transparent;
								animation: textclip 2s linear infinite;
								display: inline-block;
								font-size: 80px;
							}

							@keyframes textclip {
								to {
									background-position: 200% center;
								}
							}
						</style>
						<div class="typewriter">
							<h1 style="font-size: 30px">You've no idea how high you can fly!</h1>
						</div>
						<style>
							/* DEMO-SPECIFIC STYLES */
							.typewriter h1 {
								color: #fff;
								font-family: monospace;
								overflow: hidden;
								/* Ensures the content is not revealed until the animation */
								border-right: .15em solid orange;
								/* The typwriter cursor */
								white-space: nowrap;
								/* Keeps the content on a single line */
								margin: 0 auto;
								/* Gives that scrolling effect as the typing happens */
								letter-spacing: .15em;
								/* Adjust as needed */
								animation:
									typing 3.5s steps(30, end),
									blink-caret .5s step-end infinite;
							}

							/* The typing effect */
							@keyframes typing {
								from {
									width: 0
								}

								to {
									width: 100%
								}
							}

							/* The typewriter cursor effect */
							@keyframes blink-caret {

								from,
								to {
									border-color: transparent
								}

								50% {
									border-color: orange
								}
							}
						</style>
						</section>
					</div>
				</div>
			</div>

		</body>

		</html>