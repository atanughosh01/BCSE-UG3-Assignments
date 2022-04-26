<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
	<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
		<html>

		<head>
			<title>Travel Thru Air</title>
			<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
				integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T"
				crossorigin="anonymous">
		</head>

		<body
			style="background: black url('https://jooinn.com/images/brown-background-pattern-1.jpg?auto=compress&cs=tinysrgb&dpr=2&h=650&w=940') no-repeat scroll center; background-size: cover; height: 100vh; color: #c8cfcf;">
			<header>
				<nav class="navbar navbar-expand-md navbar-light font-weight-bold ml-auto"
					style="background-color: #D4BE94; border-bottom:20px;">
					<div>
						<a href="/UserManagement" class="navbar-brand"> Travel Thru Air </a>
					</div>

					<ul class="navbar-nav">
						<li><a href="<%=request.getContextPath()%>/list" class="nav-link">Flights</a></li>
						<li><a href="<%=request.getContextPath()%>/login" class="nav-link">Admin</a></li>
					</ul>
				</nav>
			</header>

			<div class="row" style="font-size:120%; padding-top:2em;">
				<!-- <div class="alert alert-success" *ngIf='message'>{{message}}</div> -->

				<div class="container"
					style="color:black; font-family:'Courier New', Courier, monospace; font-weight:bold; font-size:120%;">
					<h3 class="text-center" style=" font-weight:bold">List of Special Deals</h3>
					<hr>
					<br>
					<table class="table table-bordered" style=" font-weight:bold;">
						<thead>
							<tr>
								<th>ID</th>
								<th>Departure City</th>
								<th>Arrival City</th>
								<th>Cost</th>
								<th>Departure Time</th>
								<th>Arrival Time</th>
								<th>Legs</th>
								<th>Haults</th>
							</tr>
						</thead>
						<tbody>

							<c:forEach var="filterFlight" items="${filterFlight}">

								<tr>
									<td>
										<c:out value="${filterFlight.id}" />
									</td>
									<td>
										<c:out value="${filterFlight.departure_city}" />
									</td>
									<td>
										<c:out value="${filterFlight.arrival_city}" />
									</td>
									<td>
										<c:out value="${filterFlight.cost}" />
									</td>
									<td>
										<c:out value="${filterFlight.departure_time}" />
									</td>
									<td>
										<c:out value="${filterFlight.arrival_time}" />
									</td>
									<td>
										<c:out value="${filterFlight.legs}" />
									</td>
									<td>
										<c:out value="${filterFlight.path}" />
									</td>
								</tr>
							</c:forEach>

						</tbody>

					</table>
				</div>
			</div>
		</body>

		</html>