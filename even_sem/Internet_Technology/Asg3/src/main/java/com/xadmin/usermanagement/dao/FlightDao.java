package com.xadmin.usermanagement.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Time;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletContext;
import com.xadmin.usermanagement.bean.Login;
import com.xadmin.usermanagement.bean.Flight;

public class FlightDao {

	private static final String INSERT_FLIGHT_SQL = "INSERT INTO flight"
			+ "  (departure_city, arrival_city, cost, start_time, end_time, departure_time, arrival_time, legs, path) VALUES "
			+ " (?, ?, ?, ?, ?,?,?, ?, ?);";
	private static final String SELECT_FLIGHT_BY_ID = "select departure_city, arrival_city, cost, start_time, end_time, departure_time, arrival_time, legs, path from flight where id =?";
	private static final String SELECT_ALL_FLIGHT = "select * from flight";
	private static final String DELETE_FLIGHT_SQL = "delete from flight where id = ?;";
	private static final String UPDATE_FLIGHT_SQL = "update flight set departure_city = ?,arrival_city= ?, cost =?, start_time=?, end_time=?, departure_time=?, arrival_time=?, legs=?, path=? where id = ?;";
	private static final String CHECK_MANAGER_SQL = "select * from manager where username = ? and password = ?";
	private static final String SELECT_TIME_FILTER = "select id,departure_city, arrival_city, cost, start_time, end_time,departure_time,arrival_time, legs, path from flight where (case when start_time<=end_time then start_time<? and end_time>? else start_time<? or end_time>? end)";
	private static final String ONLY_DEPARTURE_DAY = "select id,departure_city, arrival_city, cost, start_time, end_time, departure_time, arrival_time, legs, path from flight where departure_city=? and departure_time>'05:00:00' and departure_time<'17:00:00'";
	private static final String ONLY_ARRIVAL_DAY = "select id,departure_city, arrival_city, cost, start_time, end_time, departure_time, arrival_time, legs, path from flight where arrival_city=? and departure_time>'05:00:00' and departure_time<'17:00:00'";
	private static final String DEPARTURE_AND_ARRIVAL_DAY = "select id,departure_city, arrival_city, cost, start_time, end_time, departure_time, arrival_time, legs, path from flight where departure_city=? and arrival_city=? and departure_time>'05:00:00' and departure_time<'17:00:00'";
	private static final String ONLY_DEPARTURE_NIGHT = "select id,departure_city, arrival_city, cost, start_time, end_time, departure_time, arrival_time, legs, path from flight where departure_city=? and (departure_time>='17:00:00' or departure_time<='05:00:00')";
	private static final String ONLY_ARRIVAL_NIGHT = "select id,departure_city, arrival_city, cost, start_time, end_time, departure_time, arrival_time, legs, path from flight where arrival_city=? and (departure_time>='17:00:00' or departure_time<='05:00:00')";
	private static final String DEPARTURE_AND_ARRIVAL_NIGHT = "select id,departure_city, arrival_city, cost, start_time, end_time, departure_time, arrival_time, legs, path from flight where departure_city=? and arrival_city=? and (departure_time>='17:00:00' or departure_time<='05:00:00')";
	private static final String ONLY_DAY = "select id,departure_city, arrival_city, cost, start_time, end_time, departure_time, arrival_time, legs, path from flight where departure_time>'05:00:00' and departure_time<'17:00:00'";
	private static final String ONLY_NIGHT = "select id,departure_city, arrival_city, cost, start_time, end_time, departure_time, arrival_time, legs, path from flight where departure_time>='17:00:00' or departure_time<='05:00:00'";

	protected Connection getConnection(ServletContext sc) {
		String jdbcURL = (String) sc.getAttribute("jdbcURL");
		String jdbcUsername = (String) sc.getAttribute("jdbcUsername");
		String jdbcPassword = (String) sc.getAttribute("jdbcPassword");
		Connection connection = null;
		try {
			connection = DriverManager.getConnection(jdbcURL, jdbcUsername, jdbcPassword);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return connection;
	}

	// public void insertFlight(Flight flight) throws SQLException {
	public void insertFlight(Flight flight, ServletContext sc) throws SQLException {
		// // System.out.println(INSERT_FLIGHT_SQL);

		try (Connection connection = getConnection(sc);
				PreparedStatement preparedStatement = connection.prepareStatement(INSERT_FLIGHT_SQL)) {
			preparedStatement.setString(1, flight.getDeparture_city());
			preparedStatement.setString(2, flight.getArrival_city());
			preparedStatement.setInt(3, flight.getCost());
			preparedStatement.setString(4, flight.getStart_time());
			preparedStatement.setString(5, flight.getEnd_time());
			preparedStatement.setString(6, flight.getDeparture_time());
			preparedStatement.setString(7, flight.getArrival_time());
			preparedStatement.setInt(8, flight.getLegs());
			preparedStatement.setString(9, flight.getPath());
			// System.out.println(preparedStatement);
			preparedStatement.executeUpdate();
		} catch (SQLException e) {
			printSQLException(e);
		}
	}

	public boolean validate(Login login, ServletContext sc) {
		boolean status = false;
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(CHECK_MANAGER_SQL);) {
			// System.out.println(preparedStatement);

			preparedStatement.setString(1, login.getUsername());
			preparedStatement.setString(2, login.getPassword());
			// System.out.println(preparedStatement);
			ResultSet rs = preparedStatement.executeQuery();
			status = rs.next();

		} catch (SQLException e) {
			printSQLException(e);
		}
		return status;
	}

	public Flight selectFlight(int id, ServletContext sc) {
		Flight flight = null;
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);
				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(SELECT_FLIGHT_BY_ID);) {
			preparedStatement.setInt(1, id);
			// System.out.println(preparedStatement);
			// Step 3: Execute the query or update query
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flight = new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path);
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flight;
	}

	public List<Flight> selectAllFlights(ServletContext sc) {

		// using try-with-resources to avoid closing resources (boiler plate code)
		List<Flight> flights = new ArrayList<>();
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(SELECT_ALL_FLIGHT);) {
			// System.out.println(preparedStatement);
			// Step 3: Execute the query or update query
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				int id = rs.getInt("id");
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flights.add(new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path));
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flights;
	}

	public static String getTime(LocalTime ldt) {
		DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm");
		return formatter.format(ldt);
	}

	public List<Flight> filterFlight(ServletContext sc) {
		List<Flight> flights = new ArrayList<>();
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(SELECT_TIME_FILTER);) {
			LocalTime locT;
			LocalTime time = LocalTime.now();
			locT = LocalTime.parse(getTime(time));
			Time t = Time.valueOf(locT);
			// System.out.println(preparedStatement);
			preparedStatement.setTime(1, t);
			preparedStatement.setTime(2, t);
			preparedStatement.setTime(3, t);
			preparedStatement.setTime(4, t);
			// System.out.println(preparedStatement);
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				int id = rs.getInt("id");
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flights.add(new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path));
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flights;

	}

	public List<Flight> departureday(String departuree_city, ServletContext sc) {
		List<Flight> flights = new ArrayList<>();
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(ONLY_DEPARTURE_DAY);) {
			preparedStatement.setString(1, departuree_city);
			// System.out.println(preparedStatement);
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				int id = rs.getInt("id");
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flights.add(new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path));
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flights;

	}

	public List<Flight> departurenight(String departuree_city, ServletContext sc) {
		List<Flight> flights = new ArrayList<>();
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(ONLY_DEPARTURE_NIGHT);) {
			preparedStatement.setString(1, departuree_city);
			// System.out.println(preparedStatement);
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				int id = rs.getInt("id");
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flights.add(new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path));
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flights;

	}

	public List<Flight> arrivalday(String arrivall_city, ServletContext sc) {
		List<Flight> flights = new ArrayList<>();
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(ONLY_ARRIVAL_DAY);) {
			preparedStatement.setString(1, arrivall_city);
			// System.out.println(preparedStatement);
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				int id = rs.getInt("id");
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flights.add(new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path));
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flights;

	}

	public List<Flight> arrivalnight(String arrivall_city, ServletContext sc) {
		List<Flight> flights = new ArrayList<>();
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(ONLY_ARRIVAL_NIGHT);) {
			preparedStatement.setString(1, arrivall_city);
			// System.out.println(preparedStatement);
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				int id = rs.getInt("id");
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flights.add(new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path));
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flights;

	}

	public List<Flight> departureAndArrivalDay(String departuree_city, String arrivall_city, ServletContext sc) {
		List<Flight> flights = new ArrayList<>();
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(DEPARTURE_AND_ARRIVAL_DAY);) {
			preparedStatement.setString(1, departuree_city);
			preparedStatement.setString(2, arrivall_city);
			// System.out.println(preparedStatement);
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				int id = rs.getInt("id");
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flights.add(new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path));
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flights;

	}

	public List<Flight> departureAndArrivalNight(String departuree_city, String arrivall_city, ServletContext sc) {
		List<Flight> flights = new ArrayList<>();
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(DEPARTURE_AND_ARRIVAL_NIGHT);) {
			preparedStatement.setString(1, departuree_city);
			preparedStatement.setString(2, arrivall_city);
			// System.out.println(preparedStatement);
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				int id = rs.getInt("id");
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flights.add(new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path));
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flights;

	}

	public List<Flight> day(ServletContext sc) {
		List<Flight> flights = new ArrayList<>();
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(ONLY_DAY);) {
			// System.out.println(preparedStatement);
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				int id = rs.getInt("id");
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flights.add(new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path));
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flights;

	}

	public List<Flight> night(ServletContext sc) {
		List<Flight> flights = new ArrayList<>();
		// Step 1: Establishing a Connection
		try (Connection connection = getConnection(sc);

				// Step 2:Create a statement using connection object
				PreparedStatement preparedStatement = connection.prepareStatement(ONLY_NIGHT);) {
			// System.out.println(preparedStatement);
			ResultSet rs = preparedStatement.executeQuery();

			// Step 4: Process the ResultSet object.
			while (rs.next()) {
				int id = rs.getInt("id");
				String departure_city = rs.getString("departure_city");
				String arrival_city = rs.getString("arrival_city");
				int cost = rs.getInt("cost");
				String start_time = rs.getString("start_time");
				String end_time = rs.getString("end_time");
				String departure_time = rs.getString("departure_time");
				String arrival_time = rs.getString("arrival_time");
				int legs = rs.getInt("legs");
				String path = rs.getString("path");
				flights.add(new Flight(id, departure_city, arrival_city, cost, start_time, end_time, departure_time,
						arrival_time, legs, path));
			}
		} catch (SQLException e) {
			printSQLException(e);
		}
		return flights;

	}

	public boolean deleteFlight(int id, ServletContext sc) throws SQLException {
		boolean rowDeleted;
		try (Connection connection = getConnection(sc);
				PreparedStatement statement = connection.prepareStatement(DELETE_FLIGHT_SQL);) {
			statement.setInt(1, id);
			rowDeleted = statement.executeUpdate() > 0;
		}
		return rowDeleted;
	}

	public boolean updateFlight(Flight flight, ServletContext sc) throws SQLException {
		boolean rowUpdated;
		try (Connection connection = getConnection(sc);
				PreparedStatement statement = connection.prepareStatement(UPDATE_FLIGHT_SQL);) {
			System.out.println("Updated User:" + statement);
			statement.setString(1, flight.getDeparture_city());
			statement.setString(2, flight.getArrival_city());
			statement.setInt(3, flight.getCost());
			statement.setString(4, flight.getStart_time());
			statement.setString(5, flight.getEnd_time());
			statement.setString(6, flight.getDeparture_time());
			statement.setString(7, flight.getArrival_time());
			statement.setInt(8, flight.getLegs());
			statement.setString(9, flight.getPath());
			statement.setInt(10, flight.getId());
			rowUpdated = statement.executeUpdate() > 0;
		}
		return rowUpdated;
	}

	private void printSQLException(SQLException ex) {
		for (Throwable e : ex) {
			if (e instanceof SQLException) {
				e.printStackTrace(System.err);
				System.err.println("SQLState: " + ((SQLException) e).getSQLState());
				System.err.println("Error Code: " + ((SQLException) e).getErrorCode());
				System.err.println("Message: " + e.getMessage());
				Throwable t = ex.getCause();
				while (t != null) {
					System.out.println("Cause: " + t);
					t = t.getCause();
				}
			}
		}
	}
}
