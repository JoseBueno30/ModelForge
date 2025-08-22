package negocio;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Persona{

	private String DNI;
	private String apellido1;
	private String apellido2;
	private String correo;
	private Integer edad;
	private String nombre;
	private Integer tlf;
	private List<Contrato> contrato;
	private List<Posesion> posesion;

	// General constraints
	// size() <= 3

	public Persona(String DNI, String apellido1, String apellido2, String correo, Integer edad, String nombre, Integer tlf) {
		this.setDNI(DNI);
		this.setApellido1(apellido1);
		this.setApellido2(apellido2);
		this.setCorreo(correo);
		this.setEdad(edad);
		this.setNombre(nombre);
		this.setTlf(tlf);
		this.contrato = new ArrayList<Contrato>();
		this.posesion = new ArrayList<Posesion>();
	}

	public String getDNI() {
		return this.DNI;
	}

	public void setDNI(String DNI) {
				this.DNI = DNI;
	}

	public String getApellido1() {
		return this.apellido1;
	}

	public void setApellido1(String apellido1) {
				this.apellido1 = apellido1;
	}

	public String getApellido2() {
		return this.apellido2;
	}

	public void setApellido2(String apellido2) {
				this.apellido2 = apellido2;
	}

	public String getCorreo() {
		return this.correo;
	}

	public void setCorreo(String correo) {
				this.correo = correo;
	}

	public Integer getEdad() {
		return this.edad;
	}

	public void setEdad(Integer edad) {
				this.edad = edad;
	}

	public String getNombre() {
		return this.nombre;
	}

	public void setNombre(String nombre) {
				this.nombre = nombre;
	}

	public Integer getTlf() {
		return this.tlf;
	}

	public void setTlf(Integer tlf) {
				this.tlf = tlf;
	}

	public List<Contrato> getContrato() {
		return Collections.unmodifiableList(this.contrato);
	}

	public void addContrato(Contrato element) {
		this.contrato.add(element);
	}

	public void removeContrato(Contrato element) {
		this.contrato.remove(element);
	}

	public List<Posesion> getPosesion() {
		return Collections.unmodifiableList(this.posesion);
	}

	public void addPosesion(Posesion element) {
		this.posesion.add(element);
	}

	public void removePosesion(Posesion element) {
		this.posesion.remove(element);
	}

}
