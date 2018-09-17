<?php

namespace AppBundle\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Method;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Component\HttpFoundation\Request;
use FOS\RestBundle\Controller\Annotations as Rest;
use FOS\RestBundle\Controller\FOSRestController;
use Symfony\Component\HttpFoundation\Response;
use FOS\RestBundle\View\View;
use Symfony\Component\Serializer\Serializer;
use Symfony\Component\Serializer\Encoder\JsonEncoder;
use Symfony\Component\Serializer\Normalizer\ObjectNormalizer;
use AppBundle\Entity\Mmf;

/**
 * Mmf controller.
 *
 * @Route("mmf")
 */
class MmfController extends FOSRestController
{
/*    public function indexAction()
    {
        $em = $this->getDoctrine()->getManager();

        $mmfs = $em->getRepository('AppBundle:Mmf')->findAll();

        return $this->render('mmf/index.html.twig', array(
            'mmfs' => $mmfs,
        ));
    }*/

    /**
     * Creates a new mmf entity.
     *
     * @Rest\Post("/new")
     */
    public function newAction(Request $request)
    {
        $em = $this->getDoctrine()->getManager();
	$encoders = array(new JsonEncoder());
	$normalizers = array(new ObjectNormalizer());
	$serializer = new Serializer($normalizers, $encoders);
$requestData=json_decode($request->getContent());
if (is_array($requestData)){
	foreach($requestData as $rD){
		$mmf = $serializer->deserialize(json_encode($rD), "AppBundle\Entity\Mmf", 'json');
       		 $em->persist($mmf);
	}
}else{
	$mmf = $serializer->deserialize($request->getContent(), "AppBundle\Entity\Mmf", 'json');
        $em->persist($mmf);
}
        $em->flush();
   	return new View("OK", Response::HTTP_OK);
    }
}
