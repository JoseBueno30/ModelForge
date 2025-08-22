package negocio;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Pedido{

	private Double descuento;
	private String fecha;
	private Double precio_final;
	private Integer valor;
	private Persona persona;
	private List<Productos_Pedido> productos_pedido;
	private Empresa vendedor;

	public Pedido(Double descuento, String fecha, Double precio_final, Integer valor, Persona persona, Empresa vendedor) {
		this.setDescuento(descuento);
		this.setFecha(fecha);
		this.setPrecio_final(precio_final);
		this.setValor(valor);
		this.setPersona(persona);
		this.productos_pedido = new ArrayList<Productos_Pedido>();
		this.setVendedor(vendedor);
	}

	public Double getDescuento() {
		return this.descuento;
	}

	public void setDescuento(Double descuento) {
				this.descuento = descuento;
	}

	public String getFecha() {
		return this.fecha;
	}

	public void setFecha(String fecha) {
				this.fecha = fecha;
	}

	public Double getPrecio_final() {
		return this.precio_final;
	}

	public void setPrecio_final(Double precio_final) {
				this.precio_final = precio_final;
	}

	public Integer getValor() {
		return this.valor;
	}

	public void setValor(Integer valor) {
				this.valor = valor;
	}

	public Persona getPersona() {
		return this.persona;
	}

	public void setPersona(Persona persona) {
		if (persona == null) {
			throw new IllegalArgumentException("persona must not be null.");
		}
		this.persona = persona;
	}

	public List<Productos_Pedido> getProductos_pedido() {
		return Collections.unmodifiableList(this.productos_pedido);
	}

	public void addProductos_pedido(Productos_Pedido element) {
		this.productos_pedido.add(element);
	}

	public void removeProductos_pedido(Productos_Pedido element) {
		this.productos_pedido.remove(element);
	}

	public Empresa getVendedor() {
		return this.vendedor;
	}

	public void setVendedor(Empresa vendedor) {
		if (vendedor == null) {
			throw new IllegalArgumentException("vendedor must not be null.");
		}
		this.vendedor = vendedor;
	}

}
