from fpdf import FPDF


def main():
    while True:
        nameInput = input("What is your name?: ")
        if nameInput:
            break

    shirtText = f"{nameInput} took CS50"

    pdf = FPDF(orientation="P", format="A4")
    pdf.add_page()
    pdf.set_font("helvetica", "B", 50)
    pdf.cell(0, 50, "CS50 Shirtificate", 0, 2, align='C')
    pdf.image("shirtificate.png", w=180, x=15, y=80)
    pdf.set_text_color(255,255,255)
    pdf.set_font("helvetica", "B", 25)
    pdf.cell(0, 180, shirtText, 0, align='C')

    pdf.output("shirtificate.pdf")


if __name__ == "__main__":
    main()