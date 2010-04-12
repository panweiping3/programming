#include <QCoreApplication>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNamedNodeMap>
#include <QFile>
#include <QDebug>

void print_attributes(QDomNamedNodeMap &attribute)
{
    if (attribute.isEmpty() == true) {
        return;
    } else {
        for (int i = 0; i < attribute.count(); ++i) {
            QDomNode node = attribute.item(i);
            if (node.isAttr()) {
                qDebug() << "Attribute[" << i << "]:" << node.toAttr().name() << ":" << node.toAttr().value(); 
            }
        }
    }
}

void print_element(QDomElement &element)
{
    // print attributes
    qDebug() << "Element tagName:" << element.tagName();
    qDebug() << "Element text   :" << element.text();
    if (element.hasAttributes()) {
        QDomNamedNodeMap map = element.attributes();
        print_attributes(map);
    }

    // print child
    if (element.hasChildNodes() == true) {
        QDomNode n = element.firstChild();
        while (!n.isNull()) {
            if (n.isElement()) {
                QDomElement e = n.toElement();
                print_element(e);            
                break;
            }
            n = n.nextSibling();
        }
    }
}


int main(int argc, char *argv[])
{
    QDomDocument doc("mydocument");
    QFile file("./rflocale.xml");
    if (!file.open(QIODevice::ReadOnly))
            return -1;
    if (!doc.setContent(&file)) {
            file.close();
            return -1;
    }
    file.close();

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = doc.documentElement();
    qDebug() << "Element tagName:" << docElem.tagName() << endl; 
    qDebug() << "Element value  :" << docElem.nodeValue() << endl; 

    print_element(docElem);
    return 0;
}
