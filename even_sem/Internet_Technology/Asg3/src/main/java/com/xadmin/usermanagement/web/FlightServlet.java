package com.xadmin.usermanagement.web;

import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Path;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.xadmin.usermanagement.dao.FlightDao;
import com.xadmin.usermanagement.bean.Flight;
import com.xadmin.usermanagement.bean.Login;

@WebServlet("/")
public class FlightServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private FlightDao FlightDao;

	public void init() {
		FlightDao = new FlightDao();
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		String action = request.getServletPath();

		try {
			switch (action) {
				case "/new":
					showNewForm(request, response);
					break;
				case "/insert":
					insertFlight(request, response);
					break;
				case "/delete":
					deleteFlight(request, response);
					break;
				case "/edit":
					showEditForm(request, response);
					break;
				case "/update":
					updateFlight(request, response);
					break;
				case "/login":
					loginManager(request, response);
					break;
				case "/logout":
					logoutManager(request, response);
					break;
				case "/filtertime":
					filterTime(request, response);
					break;
				case "/filtercity":
					filterCity(request, response);
					break;
				case "/filtercitypage":
					filtercitypage(request, response);
					break;
				case "/listadmin":
					listAdmin(request, response);
					break;
				default:
					listFlight(request, response);
					break;
			}
		} catch (SQLException ex) {
			throw new ServletException(ex);
		}

	}

	private void logoutManager(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		HttpSession session = request.getSession();
		session.removeAttribute("username");
		session.invalidate();
		response.sendRedirect("Login.jsp");
	}

	private void filtercitypage(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		RequestDispatcher dispatcher = request.getRequestDispatcher("FlightFilterCityForm.jsp");
		dispatcher.forward(request, response);
	}

	private void filterCity(HttpServletRequest request, HttpServletResponse response)
			throws IOException, ServletException {
		List<Flight> filterCityFlight = new ArrayList<Flight>();
		String departure_city = request.getParameter("departure_city");
		String arrival_city = request.getParameter("arrival_city");
		String time = request.getParameter("time");

		ServletContext sc = request.getServletContext();

		if (arrival_city.trim() != "" && departure_city.trim() != "" && time.equals("day")) {
			filterCityFlight = FlightDao.departureAndArrivalDay(departure_city.trim(), arrival_city.trim(), sc);
		} else if (arrival_city.trim() != "" && departure_city.trim() != "" && time.equals("night")) {
			filterCityFlight = FlightDao.departureAndArrivalNight(departure_city.trim(), arrival_city.trim(), sc);
		} else if (arrival_city.trim() != "" && time.equals("day")) {
			filterCityFlight = FlightDao.arrivalday(arrival_city.trim(), sc);
		} else if (arrival_city.trim() != "" && time.equals("night")) {
			filterCityFlight = FlightDao.arrivalnight(arrival_city.trim(), sc);
		} else if (departure_city.trim() != "" && time.equals("day")) {
			filterCityFlight = FlightDao.departureday(departure_city.trim(), sc);
		} else if (departure_city.trim() != "" && time.equals("night")) {
			filterCityFlight = FlightDao.departurenight(departure_city.trim(), sc);
		} else if (time.equals("night")) {
			filterCityFlight = FlightDao.night(sc);
		} else {
			filterCityFlight = FlightDao.day(sc);
		}
		request.setAttribute("filterCityFlight", filterCityFlight);
		RequestDispatcher dispatcher = request.getRequestDispatcher("FlightFilterCity.jsp");
		dispatcher.forward(request, response);

	}

	private void filterTime(HttpServletRequest request, HttpServletResponse response)
			throws IOException, ServletException {

		ServletContext sc = request.getServletContext();
		List<Flight> filterTimeFlight = FlightDao.filterFlight(sc);
		request.setAttribute("filterFlight", filterTimeFlight);
		RequestDispatcher dispatcher = request.getRequestDispatcher("FlightFilterTime.jsp");
		dispatcher.forward(request, response);

	}

	private void loginManager(HttpServletRequest request, HttpServletResponse response) throws IOException {

		ServletContext sc = request.getServletContext();
		String uname = request.getParameter("username");
		String password = request.getParameter("password");
		Login login = new Login();
		login.setUsername(uname);
		login.setPassword(password);

		if (FlightDao.validate(login, sc)) {

			HttpSession session = request.getSession();
			session.setAttribute("username", uname);
			response.sendRedirect("listadmin");
		} else {
			response.sendRedirect("Login.jsp");
		}

	}

	private void listFlight(HttpServletRequest request, HttpServletResponse response)
			throws SQLException, IOException, ServletException {
		ServletContext sc = request.getServletContext();
		List<Flight> listFlight = FlightDao.selectAllFlights(sc);
		System.out.println("11");
		request.setAttribute("listFlight", listFlight);
		RequestDispatcher dispatcher = request.getRequestDispatcher("FlightListUser.jsp");
		dispatcher.forward(request, response);
	}

	private void listAdmin(HttpServletRequest request, HttpServletResponse response)
			throws SQLException, IOException, ServletException {
		ServletContext sc = request.getServletContext();
		List<Flight> listFlight = FlightDao.selectAllFlights(sc);
		System.out.println("11");

		for (int i = 0; i < listFlight.size(); i++) {
			String path = listFlight.get(i).getPath();
			List<String> arrPath = Arrays.asList(path.split(","));
			int arrLen = arrPath.size();
			listFlight.get(i).setLegs((arrLen + 1));
		}

		request.setAttribute("listFlight", listFlight);
		RequestDispatcher dispatcher = request.getRequestDispatcher("FlightList.jsp");
		dispatcher.forward(request, response);

	}

	private void showNewForm(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		RequestDispatcher dispatcher = request.getRequestDispatcher("FlightForm.jsp");
		dispatcher.forward(request, response);
	}

	private void showEditForm(HttpServletRequest request, HttpServletResponse response)
			throws SQLException, ServletException, IOException {
		ServletContext sc = request.getServletContext();
		int id = Integer.parseInt(request.getParameter("id"));
		Flight flight = FlightDao.selectFlight(id, sc);
		System.out.print(flight);
		RequestDispatcher dispatcher = request.getRequestDispatcher("FlightForm.jsp");
		request.setAttribute("flight", flight);
		dispatcher.forward(request, response);

	}

	private void insertFlight(HttpServletRequest request, HttpServletResponse response)
			throws SQLException, IOException {
		ServletContext sc = request.getServletContext();
		String departure_city = request.getParameter("departure_city");
		String arrival_city = request.getParameter("arrival_city");
		int cost = Integer.parseInt(request.getParameter("cost"));
		String start_time = request.getParameter("start_time");
		String end_time = request.getParameter("end_time");
		String departure_time = request.getParameter("departure_time");
		String arrival_time = request.getParameter("arrival_time");
		int legs = Integer.parseInt(request.getParameter("legs"));
		String path = request.getParameter("path");
		Flight newFlight = new Flight(departure_city, arrival_city, cost, start_time, end_time, departure_time,
				arrival_time, legs, path);
		FlightDao.insertFlight(newFlight, sc);
		response.sendRedirect("listadmin");
	}

	private void updateFlight(HttpServletRequest request, HttpServletResponse response)
			throws SQLException, IOException {
		ServletContext sc = request.getServletContext();
		int id = Integer.parseInt(request.getParameter("id"));
		String departure_city = request.getParameter("departure_city");
		String arrival_city = request.getParameter("arrival_city");
		int cost = Integer.parseInt(request.getParameter("cost"));
		String start_time = request.getParameter("start_time");
		String end_time = request.getParameter("end_time");
		String departure_time = request.getParameter("departure_time");
		String arrival_time = request.getParameter("arrival_time");
		int legs = Integer.parseInt(request.getParameter("legs"));
		String path = request.getParameter("path");
		Flight updatedFlight = new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
				arrival_time, legs, path);
		FlightDao.updateFlight(updatedFlight, sc);
		response.sendRedirect("listadmin");
	}

	private void deleteFlight(HttpServletRequest request, HttpServletResponse response)
			throws SQLException, IOException {
		ServletContext sc = request.getServletContext();
		int id = Integer.parseInt(request.getParameter("id"));
		FlightDao.deleteFlight(id, sc);
		response.sendRedirect("listadmin");

	}
}
